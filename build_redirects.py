import os
import glob

def find_files(directory):
    pattern = os.path.join(directory, "**", "*.md")
    return glob.glob(pattern, recursive=True)

def add_frontmatter_config(file_path, config_key, config_value):
    with open(file_path, "r") as file:
        content = file.read()

    parts = content.split("---")
    if len(parts) < 3:
        raise ValueError("The file does not contain valid FrontMatter")

    frontmatter = parts[1].strip()
    rest_of_content = "---".join(parts[2:])

    frontmatter_lines = frontmatter.split("\n")

    key_exists = False
    for i, line in enumerate(frontmatter_lines):
        if line.startswith(f"{config_key}:"):
            frontmatter_lines[i] = f"{config_key}: {config_value}"
            key_exists = True
            break

    if not key_exists:
        frontmatter_lines.append(f"{config_key}: {config_value}")

    frontmatter = "\n".join(frontmatter_lines)

    updated_content = f"---\n{frontmatter}\n---{rest_of_content}"

    with open(file_path, "w") as file:
        file.write(updated_content)

files = find_files("./docs")
files.append("./index.md")
files.append("./404.html")

for file in files:
    relativePath = file.replace("./docs/", "").replace("./", "").replace("index.md", "").replace(".md", "")

    # The following redirects are changed because in Docusaurus a category
    # doesn't necessarily have a page associated with it

    if (relativePath == "introduction/"):
        relativePath = "introduction/what-is-acap"

    if (relativePath == "get-started/" or relativePath == "get-started/set-up-developer-environment/"):
        relativePath = "get-started/set-up-developer-environment/pre-requisites"

    if (relativePath == "api/"):
        relativePath = "api/native-sdk-api"

    if (relativePath == "service/"):
        relativePath = "service/acap-service-portal"

    if (relativePath == "acap-sdk-version-3/"):
        relativePath = "acap-sdk-version-3/introduction"

    if (relativePath == "acap-sdk-version-3/develop-applications/"):
        relativePath = "acap-sdk-version-3/develop-applications/application-project-structure"

    if (relativePath == "acap-sdk-version-3/services-for-partners/"):
        relativePath = "acap-sdk-version-3/services-for-partners/package-signing"

    # This page ios removed in the migration, redirect to the root of the ACAP
    # documentation
    if (relativePath == "licenses/"):
        relativePath = ""
    
    # Redirect them to the root of the ACAP documentation    
    if (relativePath == "404.html"):
        relativePath = ""
        
    if (not relativePath.endswith("release-notes/") and "release-notes/" in relativePath):
        relativePath += "/"

    url = f"https://developer.axis.com/acap/{relativePath}"

    add_frontmatter_config(file, "redirect_to", url)
    