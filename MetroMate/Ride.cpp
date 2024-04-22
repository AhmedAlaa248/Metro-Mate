#include "Ride.h"

Ride::Ride()
{
}

Ride::Ride(int rideId, string src, string dest, int station_id)
{
    id = rideId;
    source = src;
    destination = dest;
    stationId = station_id;

}


