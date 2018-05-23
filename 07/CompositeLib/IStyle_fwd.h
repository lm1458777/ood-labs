#pragma once

class IFillStyle;
using IFillStylePtr = std::shared_ptr<IFillStyle>;
using IFillStyleUniquePtr = std::unique_ptr<IFillStyle>;

class ILineStyle;
using ILineStylePtr = std::shared_ptr<ILineStyle>;
using ILineStyleUniquePtr = std::unique_ptr<ILineStyle>;
