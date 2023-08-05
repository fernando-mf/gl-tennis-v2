#include "TennisRacketModel.h"

TennisRacketModel::TennisRacketModel(const vec3& position)
        : modelPosition(position),
          modelRotationXAxis(0.0f),
          modelRotationYAxis(0.0f),
          modelRotationZAxis(0.0f),
          modelLowerarmRotationXAxis(0.0f),
          modelLowerarmRotationYAxis(0.0f),
          modelLowerarmRotationZAxis(0.0f),
          modelHandRotationXAxis(0.0f),
          modelHandRotationYAxis(0.0f),
          modelHandRotationZAxis(0.0f),
          modelScale(vec3(1.0f, 1.0f, 1.0f)),
          modelDisplacementRate(5.0f),
          modelRotationRate(20.0f),
          modelScaleRate(0.03f) {
}

// Accessors
vec3 TennisRacketModel::getModelPosition() const {
    return modelPosition;
}

float TennisRacketModel::getModelRotationXAxis() const {
    return modelRotationXAxis;
}

float TennisRacketModel::getModelRotationYAxis() const {
    return modelRotationYAxis;
}

float TennisRacketModel::getModelRotationZAxis() const {
    return modelRotationZAxis;
}

float TennisRacketModel::getModelLowerarmRotationXAxis() const {
    return modelLowerarmRotationXAxis;
}

float TennisRacketModel::getModelLowerarmRotationYAxis() const {
    return modelLowerarmRotationYAxis;
}

float TennisRacketModel::getModelLowerarmRotationZAxis() const {
    return modelLowerarmRotationZAxis;
}

float TennisRacketModel::getModelHandRotationXAxis() const {
    return modelHandRotationXAxis;
}

float TennisRacketModel::getModelHandRotationYAxis() const {
    return modelHandRotationYAxis;
}

float TennisRacketModel::getModelHandRotationZAxis() const {
    return modelHandRotationZAxis;
}

vec3 TennisRacketModel::getModelScale() const {
    return modelScale;
}

float TennisRacketModel::getModelDisplacementRate() const {
    return modelDisplacementRate;
}

float TennisRacketModel::getModelRotationRate() const {
    return modelRotationRate;
}

float TennisRacketModel::getModelScaleRate() const {
    return modelScaleRate;
}

// Mutators
void TennisRacketModel::setModelPosition(const vec3& position) {
    modelPosition = position;
}

void TennisRacketModel::setModelRotationXAxis(float rotation) {
    modelRotationXAxis = rotation;
}

void TennisRacketModel::setModelRotationYAxis(float rotation) {
    modelRotationYAxis = rotation;
}

void TennisRacketModel::setModelRotationZAxis(float rotation) {
    modelRotationZAxis = rotation;
}

void TennisRacketModel::setModelLowerarmRotationXAxis(float rotation) {
    modelLowerarmRotationXAxis = rotation;
}

void TennisRacketModel::setModelLowerarmRotationYAxis(float rotation) {
    modelLowerarmRotationYAxis = rotation;
}

void TennisRacketModel::setModelLowerarmRotationZAxis(float rotation) {
    modelLowerarmRotationZAxis = rotation;
}

void TennisRacketModel::setModelHandRotationXAxis(float rotation) {
    modelHandRotationXAxis = rotation;
}

void TennisRacketModel::setModelHandRotationYAxis(float rotation) {
    modelHandRotationYAxis = rotation;
}

void TennisRacketModel::setModelHandRotationZAxis(float rotation) {
    modelHandRotationZAxis = rotation;
}

void TennisRacketModel::setModelScale(const vec3& scale) {
    modelScale = scale;
}

void TennisRacketModel::setModelDisplacementRate(float rate) {
    modelDisplacementRate = rate;
}

void TennisRacketModel::setModelRotationRate(float rate) {
    modelRotationRate = rate;
}

void TennisRacketModel::setModelScaleRate(float rate) {
    modelScaleRate = rate;
}