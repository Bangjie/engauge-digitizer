#ifndef EXPORT_FILE_FUNCTIONS_H
#define EXPORT_FILE_FUNCTIONS_H

#include "ExportFileAbstractBase.h"
#include "ExportValues.h"
#include <QStringList>
#include <QVector>

class Document;
class DocumentModelExport;
class QTextStream;
class Transformation;

/// Strategy class for exporting to a file. This strategy is external to the Document class so that class is simpler.
class ExportFileFunctions : public ExportFileAbstractBase
{
public:
  /// Single constructor.
  ExportFileFunctions();

  /// Export Document points according to the settings. The DocumentModelExport inside the Document is ignored so
  /// DlgSettingsExport can supply its own DocumentModelExport when previewing what would be exported.
  void exportToFile (const DocumentModelExport &modelExport,
                     const Document &document,
                     const Transformation &transformation,
                     QTextStream &str) const;

private:

  /// Deallocate the 2D y/radius array allocated by initializeYRadiusValues
  void destroyYRadiusValues (QVector<QVector<QString*> > &yRadiusValues) const;

  void exportAllPerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                           const Document &document,
                                           const QStringList &curvesIncluded,
                                           const ExportValues &xThetaValues,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           QTextStream &str) const;
  void exportOnePerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                           const Document &document,
                                           const QStringList &curvesIncluded,
                                           const ExportValues &xThetaValues,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           QTextStream &str) const;

  /// Allocate a 2D y/radius array indexed by (included) curve and x/theta.
  /// Array rows and columns are set up so yRadiusValues[N] gives vector for Nth curve. Values are strings
  /// so non-applicable entries can be blank
  void initializeYRadiusValues (const QStringList &curvesIncluded,
                                const ExportValues &xThetaValuesMerged,
                                QVector<QVector<QString*> > &yRadiusValues) const;

  double linearlyInterpolate (const Points &points,
                              double xThetaValue,
                              const Transformation &transformation) const;
  void loadYRadiusValues (const DocumentModelExport &modelExport,
                          const Document &document,
                          const QStringList &curvesIncluded,
                          const Transformation &transformation,
                          const ExportValues &xThetaValues,
                          QVector<QVector<QString*> > &yRadiusValues) const;
  void loadYRadiusValuesForCurveInterpolatedSmooth (const Points &points,
                                                    const ExportValues &xThetaValues,
                                                    const Transformation &transformation,
                                                    QVector<QString*> &yRadiusValues) const;
  void loadYRadiusValuesForCurveInterpolatedStraight (const Points &points,
                                                      const ExportValues &xThetaValues,
                                                      const Transformation &transformation,
                                                      QVector<QString*> &yRadiusValues) const;
  void loadYRadiusValuesForCurveRaw (const Points &points,
                                     const ExportValues &xThetaValues,
                                     const Transformation &transformation,
                                     QVector<QString*> &yRadiusValues) const;

  /// Output 2D y/radius array along with x/theta vector in first column
  void outputXThetaYRadiusValues (const DocumentModelExport &modelExport,
                                  const QStringList &curvesIncluded,
                                  const ExportValues &xThetaValuesMerged,
                                  QVector<QVector<QString*> > &yRadiusValues,
                                  const QString &delimiter,
                                  QTextStream &str) const;
};

#endif // EXPORT_FILE_FUNCTIONS_H