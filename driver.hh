#ifndef DRIVER_HH
#define DRIVER_HH

#include "file_info.hh"
#include "file_part.hh"
#include "figshare_gateway.hh"
#include "part_preparer.hh"

class Driver {
public:
    Driver(
        FigshareGateway* gateway,
        PartPreparer* partPreparer
    ) : gateway(gateway), partPreparer(partPreparer) { }
    void handlePart(const FileInfo sourceFile, const FilePart partSpec) const;

private:
    FigshareGateway* gateway;
    PartPreparer* partPreparer;
};

#endif // DRIVER_HH
