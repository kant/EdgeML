// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef __DATA_H__
#define __DATA_H__

#include "pre_processor.h"

namespace EdgeML
{
  enum DataFormat
  {
    undefinedData, interfaceIngestFormat, MNISTFormat, tsvFormat, libsvmFormat
  };

  enum ProblemFormat
  {
    undefinedProblem, binary, multiclass, multilabel
  };

  enum InitializationFormat
  {
    undefinedInitialization, predefined, perClassKmeans, overallKmeans, sample
  };

  enum NormalizationFormat
  {
    undefinedNormalization, none, l2, minMax
  };

  enum DataIngestType
  {
    FileIngest, InterfaceIngest
  };

  struct DataFormatParams
  {
    dataCount_t numTrainPoints;
    dataCount_t numTestPoints;
    labelCount_t numLabels;
    featureCount_t dimension;
  };

  struct SparseDataPoint
  {
    const FP_TYPE *values;
    const featureCount_t *indices;
    const featureCount_t numIndices;
    const labelCount_t *labels;
    const labelCount_t numLabels;
  };


  struct DenseDataPoint
  {
    const FP_TYPE *values;
    const labelCount_t *labels;
    const labelCount_t numLabels;
  };

  class Data
  {
    DataFormatParams formatParams;
    DataIngestType ingestType;

    std::vector<Trip> sparseDataHolder;
    std::vector<Trip> sparseLabelHolder;
    std::vector<FP_TYPE> denseDataHolder;
    dataCount_t numPointsIngested;

  public:
    bool isDataLoaded;

    MatrixXuf trainData, trainLabel;
    MatrixXuf testData, testLabel;

    SparseMatrixuf Xtrain, Ytrain;
    SparseMatrixuf Xtest, Ytest;

    void loadDataFromFile(
      DataFormat format,
      std::string infile,
      std::string outfile);

    Data(DataIngestType dataIngestType,
      DataFormatParams formatParams);
    ~Data() {};

    void feedSparseData(const SparseDataPoint& point);
    void feedDenseData(const DenseDataPoint& point);
    void finalizeData();

    inline DataIngestType getIngestType() { return ingestType; }
  };

  void minMaxNormalize(SparseMatrixuf& dataMatrix, SparseMatrixuf& valMatrix);
  void l2Normalize(SparseMatrixuf& dataMatrix);
  void meanVarNormalize(SparseMatrixuf& dataMatrix, MatrixXuf& mean, MatrixXuf& variance);
}
#endif
