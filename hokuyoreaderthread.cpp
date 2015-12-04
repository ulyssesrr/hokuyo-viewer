#include "hokuyoreaderthread.h"

#include <iostream>

#include <QDebug>
#include <QMessageBox>
#include <QApplication>

#include <flexiport-2/flexiport/flexiport.h>
#include <hokuyoaist/hokuyo_errors.h>

HokuyoReaderThread::HokuyoReaderThread(QObject *parent) : QThread(parent)
{

}

void HokuyoReaderThread::run()
{
    std::string port_options("type=serial,device=/dev/ttyACM0,timeout=1");

    try
    {
        hokuyoaist::Sensor laser; // Laser scanner object
        //laser.set_verbose(true);

        // Open the laser
        laser.open(port_options);

        // Calibrate the laser time stamp
        std::cout << "Calibrating laser time\n";
        laser.calibrate_time();
        std::cout << "Calculated offset: " << laser.time_offset() << "ns\n";
        std::cout << "Calculated drift rate: " << laser.drift_rate() << '\n';
        std::cout << "Calculated skew alpha: " << laser.skew_alpha() << '\n';

        // Turn the laser on
        laser.set_power(true);

        // Get some laser info
        std::cout << "Laser sensor information:\n";
        hokuyoaist::SensorInfo info;
        laser.get_sensor_info(info);
        std::cerr << info.as_string();

        // Get range data
        while (1) {
            hokuyoaist::ScanData* data = new hokuyoaist::ScanData;
            laser.get_new_ranges(*data, -1, -1, 1);
            //qDebug() << "PRE-EMIT " << data->ranges_length();
            emit onScanReading(data);
        }

        //std::cout << "Measured data:\n";
        //std::cout << data.as_string();

        // Close the laser
        laser.close();
    }
    catch(hokuyoaist::BaseError &e)
    {
        std::cerr << "Caught exception: " << e.what() << '\n';
        emit onErrorInitializingHokuyo();
    }
    catch(flexiport::PortException &e)
    {
        std::cerr << "Caught exception: " << e.what() << '\n';
//        return;
        emit onErrorOpeningHokuyo();
    }
}
