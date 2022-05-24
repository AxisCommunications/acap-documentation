---
layout: page
parent: Develop applications
title: Camera calibration
nav_order: 6
---

# Camera calibration

Images captured by an Axis camera are sometimes visibly distorted in the edges. That is because Axis cameras prioritize capturing a wide area over producing rectilinear images. Distortion can make it difficult to detect objects or to measure distances.

To correct this, we can calibrate the image and straighten it. In this guide, we'll explain the [calibration procedure](#calibration-procedure) and the [validation procedure](#validation-procedure) with some [validation results](#validation-results). You can find the code in the [acap-sdk-tools](https://github.com/AxisCommunications/acap-sdk-tools/tree/main/camera-calibration-for-lens-distortion) repository.

## Quickstart

The following instructions are a summary of the steps to follow. For a deeper explanation, refer to the next sections.

1. [Create](https://github.com/ethz-asl/kalibr/wiki/calibration-targets#a-aprilgrid) and print an AprilTag grid.
2. Take sample pictures with the Axis camera pointing towards the AprilTag grid, including different positions and orientations of the grid.
3. Modify the parameters related to pattern creation and update the images directory path in [`main.cpp`](https://github.com/AxisCommunications/acap-sdk-extras/blob/main/camera-calibration/main.cpp).
4. Build the Docker image that will download and compile all the calibration code.

    ```sh
    docker build . -t <APP_IMAGE>
    ```

    where `<APP_IMAGE>` is the desired name of the Docker image, e.g. *calibration*

5. Run the Docker image. The calibration code will automatically run to obtain the estimated calibration parameters, which are saved in `config.cfg`.

    ```sh
    docker run -it --name <APP_CONTAINER> <APP_IMAGE>
    ```

    where `<APP_CONTAINER>` is the desired name of the Docker container, e.g. *calibration-container*

6. Copy the calibration parameters.

    ```sh
    docker cp calibration:/app/config.cfg .
    ```

## Calibration procedure

There are three concepts to take into account when talking about calibration:

- Distortion coefficients: define the distortion produced by pinhole cameras (radial and tangential).
- Intrinsic camera parameters: define the distortion produced by the camera lens (focal length, optical centers).
- Extrinsic parameters: define the relationship between the real world and what is captured (translation or rotation).

All these parameters must be found to create a mapping between the real world and the image plane. To do that, you need to build a setup with some points in the real world (**object points**) and in the image (**image points**). The easiest way is to create a well-defined pattern that makes it easy to get both, print it, and take different sample pictures. It's important that the pattern occupies the distorted area of the frame and that at least 10 are taken so that the matching algorithm can learn the distortion.

To get the image points, we use an [AprilTag detection algorithm](https://github.com/ethz-asl/ethzasl_apriltag2) that detects the 4 corners of the tags and its ID. It was originally developed at MIT and adapted by ETH Zurich. For the object points, it depends on which pattern you use. Using a grid is typical, like a chessboard or an MxN grid with [AprilTags](https://april.eecs.umich.edu/software/apriltag). For the latter, we have defined `src/AprilGrid.cc` with function `objpoints()` that returns object points with the help of the parameters used to create the pattern. We need the detection to map the object points correctly depending on which tag has been detected. The class also includes the function to get the image points.

To create the AprilTag grid, ETH provides a [tool](https://github.com/ethz-asl/kalibr/wiki/calibration-targets#a-aprilgrid) to do so by providing `NUM_COLS`, `NUM_ROWS`, the size of each tag in meters `TAG_WIDTH_M` and the space/size ratio between them `TAG_SPACING_PERCENT`. With these parameters, you can personalize the grid and adapt it to your capturing resolution.

```bash
kalibr_create_target_pdf --type apriltag --nx <NUM_COLS> --ny <NUM_ROWS> --tsize <TAG_WIDTH_M> --tspace <TAG_SPACING_PERCENT>
```

<!-- The object points are easy to get by setting an origin (0,0) and measuring the corners' positions. Theoretically, object points are defined in the 3D space but we can simplify it to two dimensions if we assume one of the three to be constant. -->

Going through the main file, `main.cpp`, the pattern parameters are set, then the calibration is performed in `calibration()` and, finally, the found parameters are saved using `writeconfig()`. The initial calibration steps for each sample image consist of:

1. Read image.
2. Perform AprilTag detection to get the position of the 4 corners and its ID.
3. Get image points and object points. The points are valid only if a defined amount of tags is detected (parameter `threshold`).

With all the obtained points, it then performs the calibration using `cv::calibrateCamera()`. This function estimates the intrinsic camera parameters (camera matrix), the distortion coefficients, and the extrinsic parameters (rotation and translation vectors) for each image. Additionally, it returns the overall Root Mean Square (RMS) re-projection error. The function works iteratively to minimize this error. The reason why the error might be higher than expected is most likely related to the quality or amount of sample images. Make sure that the pattern goes over the areas with higher distortion (corners). Regarding the amount, too many similar pictures can cause overfitting, but too little might not let the algorithm learn the parameters properly. Some sample images can be found in the [acap-sdk-tools](https://github.com/AxisCommunications/acap-sdk-tools/tree/main/camera-calibration-for-lens-distortion/data) repository.

### Straightening

After getting the parameters, we can easily straighten the image with `cv::undistort()`. Additionally, we can tweak the camera matrix to scale the straightening using an additional command, `cv::getOptimalNewCameraMatrix()`, using the parameter `alpha`. This last step is not necessary to straighten.

```cpp
new_camera_mat = cv::getOptimalNewCameraMatrix(camera_mat, distortion_coeff, cv::Size(Grid.rows,Grid.columns), alpha);
cv::undistort(sample_im, output_im, camera_mat, distortion_coeff, new_camera_mat);
```

## Validation procedure

In the previous section, we saw that `cv::calibrateCamera()` returns the overall RMS re-projection error. This measure is calculated by adding all the square distances between the image points and the estimated image points, calculated by projecting the object points to the image plane using the estimated parameters. This value summarizes the number of pixels with error.

To get a more in-depth idea of where the error comes from, we can calculate an error for each tag. This way, we'll know in which areas there is still some distortion. `cv::projectPoints()` projects the object points to the image plane, given the estimated parameters (rotation matrix, translation matrix, camera matrix, and distortion coefficients). Remember that each tag has 4 points (the corners).

### Validation results

In the following table, the overall Root Mean Square (RMS) re-projection error in pixels is reported. The images were captured with the default optics configuration and using autofocus before the first picture, so that the camera is focused on the grid. The images that were used to get these results are in the [acap-sdk-tools](https://github.com/AxisCommunications/acap-sdk-tools/tree/main/camera-calibration-for-lens-distortion/data) repository.

| Camera | Wide capturing (No zoom) | Tele (Full zoom) |
| :- | :- | :- |
| Q1656 | 0.9 | 1.1 |

## License

The AprilTags C++ library is available as open source under GNU LGPL version 2.1.
