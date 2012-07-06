/*****************************************************************************
 *   IGATO - Interplanetary Gravity Assist Trajectory Optimizer              *
 *   Copyright (C) 2012 Jason Bryan (Jmbryan10@gmail.com)                    *
 *                                                                           *
 *   IGATO is free software; you can redistribute it and/or modify           *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   IGATO is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with IGATO; if not, see http://www.gnu.org/licenses/              *
 *****************************************************************************/

#include "OrbitalBody.h"
#include "Base.h"

OrbitalBody::OrbitalBody()
{
}

OrbitalBody::OrbitalBody(const std::string& name, double radius, double mu)
{
    SetName(name);
    SetRadius(radius);
    SetMu(mu);
}

void OrbitalBody::SetName(const std::string& name)
{
    _name = name;
}

void OrbitalBody::SetRadius(double radius)
{
    _radius = radius;
}

void OrbitalBody::SetMu(double mu)
{
    _mu = mu;
}