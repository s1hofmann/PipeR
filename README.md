# pipeline_framework
A framework for pattern recognition pipelines.

## A little more detail
This framework here is one of my "bigger" spare-time projects.
It's intended to get developers up and running with a pattern recognition pipeline.

It evolved from my work on my master's project at the university. While working on my project, I needed to build a pipeline to perform text detection on historical document images.

It should include the following steps:

1. Preprocessing
2. Feature Extraction
3. Dimensionality Reduction
4. Encoding
5. Classification

Since doing things on your own actually helps you to learn lots of things, I started from scratch. But along my way I soon realized that a lot of the boilerplate I was writing to glue my pipeline together would also be written by the next student who would need a PR pipeline.

Since I like to design frameworks, I decided to build a modular framework for pattern recognition pipelines in my spare-time.

## Status
- [x] Utils
  - [x] Logging
  - [x] I/O
  - [x] Commandline Arguments

- [ ] Core
  - [x] Clustering
    - [x] K-Means
    - [x] DBSCAN
    - [ ] GMM
  - [x] Dimensionality Reduction
    - [x] PCA
  - [ ] Encoding
    - [x] BoW
    - [x] VLAD
    - [ ] Fisher Vectors
  - [ ] Feature Extraction
    - [x] SIFT
    - [ ] Zernike Moments
    - [ ] OTC
  - [ ] Machine Learning
    - [x] Linear SVM
  - [ ] Preprocessing
    - [x] Vesselfilter
    - [ ] Binarization


This list is by no means complete and will be extended in the future.
