﻿// This file is part of the SpeedCrunch project
// Copyright (C) 2013 @heldercorreia
// Copyright (C) 2015 Pol Welter <polwelter@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.

#include "../core/numberformatter.h"

#include "core/coresettings.h"
#include "../math/quantity.h"

QString NumberFormatter::format(Quantity q)
{
    CoreSettings* settings = CoreSettings::instance();

    Quantity::Format format = q.format();
    if (format.base == Quantity::Format::Base::Null) {
        switch (settings->resultFormat) {
        case 'b':
            format.base = Quantity::Format::Base::Binary;
            format.mode = Quantity::Format::Mode::Fixed;
            break;
        case 'o':
            format.base = Quantity::Format::Base::Octal;
            format.mode = Quantity::Format::Mode::Fixed;
            break;
        case 'h':
            format.base = Quantity::Format::Base::Hexadecimal;
            format.mode = Quantity::Format::Mode::Fixed;
            break;
        case 'n':
            format.base = Quantity::Format::Base::Decimal;
            format.mode = Quantity::Format::Mode::Engineering;
            break;
        case 'f':
            format.base = Quantity::Format::Base::Decimal;
            format.mode = Quantity::Format::Mode::Fixed;
            break;
        case 'e':
            format.base = Quantity::Format::Base::Decimal;
            format.mode = Quantity::Format::Mode::Scientific;
            break;
        case 'g':
        default:
            format.base = Quantity::Format::Base::Decimal;
            format.mode = Quantity::Format::Mode::General;
            break;
        }
    }
    if (format.mode == Quantity::Format::Mode::Null)
        format.mode = Quantity::Format::Mode::General;
    if (format.precision == Quantity::Format::PrecisionNull)
        format.precision = settings->resultPrecision;
    if (format.notation == Quantity::Format::Notation::Null) {
        if (settings->resultFormatComplex == 'c')
            format.notation = Quantity::Format::Notation::Cartesian;
        else if (settings->resultFormatComplex == 'p')
            format.notation = Quantity::Format::Notation::Polar;
    }

    QString result = DMath::format(q, format);

    if (settings->radixCharacter() == ',')
        result.replace('.', ',');

    return result;
}
