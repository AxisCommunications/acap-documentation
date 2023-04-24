---
layout: page
parent: FAQ
title: Security
nav_order: 2
---

<!-- omit in toc -->
# Security

<!-- omit in toc -->
## Table of contents

- [Sign ACAP applications](#sign-acap-applications)
- [Cybersecurity and protecting models](#cybersecurity-and-protecting-models)

## Sign ACAP applications

Signed ACAP applications, and having the Axis device verify the signature on installation, is supported in Axis devices as of AXIS OS 9.20.

With AXIS OS 11.2, an interface was added to [VAPIX](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050) to control whether the device will only accept signed ACAP applications or not, improving the device's security posture. As of AXIS OS 11.2, this is an opt-in feature.

We recommend that you disable this check while developing your ACAP application. Once you are ready to use your application in production, you can sign it using the [ACAP Service Portal](../service-for-partners/acap-service-portal.md).

By signing your application, you add a level of protection during distribution. An installer or end-customer can trust that the application hasn't been tampered with, and they can also verify that it's your company that has built the application.

Members of the [Axis Technology Integration Partner (TIP)](https://www.axis.com/partner/technology-integration-partner-program) program automatically have access to the ACAP Service Portal. If you're not a partner, given you qualify for the program requirements, you can apply for access to the ACAP Service Portal. You need to have a registered company when applying.

## Cybersecurity and protecting models

How is my ACAP software and potential deep learning model (Intellectual Property) protected in the device?

An ACAP application is like any software that comes in a package. It can be inspected and reverse-engineered. We understand that anyone investing resources into software is concerned about someone copying it. It has been proven repeatedly that it's impossible to prevent someone from copying software available on the market. Even sophisticated copy protection mechanisms are commonly breached. However, it is hard to copy your know-how, support offering, partner network, etc. On top of this, legal action can be taken against trademark and patent infringements. Even if it's technically possible, it would, from a business perspective, not be possible.

When developing a deep learning model and AI applications, the most valuable assets are the knowledge about the end-customer and their problems. This know-how guides you through collecting the right training data, developing relevant system integrations, and building the business logic. This is an ongoing process where you add more and more value as your business and know-how grow.

Stealing parts of the solution from a device will not give anyone access to the training data to evolve the model. The same logic applies to Axis AI models and software that we have invested much in developing.

Axis provides a licensing mechanism that prevents ACAP applications from running without a valid license key. This gives you a mechanism to track how your ACAP is being used.
