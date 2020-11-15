#include <algorithm>
#include <utility>

#include <pl/begin_end_macro.hpp>

#include <cl/exception.hpp>

#include "configuration.hpp"

namespace cm {
namespace {
/*!
 * \brief Checks if the iterator range given contains `value`.
 * \tparam Iterator The type of the iterator.
 * \tparam Ty The type of the value.
 * \param begin The start of the iterator range.
 * \param end The end iterator of the iterator range.
 * \param value The vaule to search for.
 * \return true if [begin;end) contains `value`; false otherwise.
 * \note Uses a half open range.
 **/
template<typename Iterator, typename Ty>
[[nodiscard]] bool contains(Iterator begin, Iterator end, const Ty& value)
{
  return std::any_of(begin, end, [&value](const auto& currentValue) {
    return currentValue == value;
  });
}

inline constexpr std::array<bool, 2> booleans{{false, true}};
} // namespace

Configuration::Builder::Builder() noexcept
  : m_skipWindow{tl::nullopt}
  , m_deleteTooClose{tl::nullopt}
  , m_deleteTooLowVariance{tl::nullopt}
  , m_imu{tl::nullopt}
  , m_segmentationKind{tl::nullopt}
  , m_windowSize{tl::nullopt}
  , m_filterKind{tl::nullopt}
{
}

Configuration::Builder& Configuration::Builder::skipWindow(bool value)
{
  m_skipWindow = value;
  return *this;
}

Configuration::Builder& Configuration::Builder::deleteTooClose(bool value)
{
  m_deleteTooClose = value;
  return *this;
}

Configuration::Builder& Configuration::Builder::deleteTooLowVariance(bool value)
{
  m_deleteTooLowVariance = value;
  return *this;
}

Configuration::Builder& Configuration::Builder::imu(Imu value)
{
  m_imu = value;
  return *this;
}

Configuration::Builder& Configuration::Builder::segmentationKind(
  std::string value)
{
  m_segmentationKind = value;
  return *this;
}

Configuration::Builder& Configuration::Builder::windowSize(std::size_t value)
{
  m_windowSize = value;
  return *this;
}

Configuration::Builder& Configuration::Builder::filterKind(std::string value)
{
  m_filterKind = value;
  return *this;
}

Configuration Configuration::Builder::build() const
{
// Check is initialized.
#define CM_ENSURE_HAS_VALUE(dataMember)               \
  PL_BEGIN_MACRO                                      \
  if (!dataMember.has_value()) {                      \
    CL_THROW_FMT("\"{}\" was nullopt!", #dataMember); \
  }                                                   \
  PL_END_MACRO

  CM_ENSURE_HAS_VALUE(m_skipWindow);
  CM_ENSURE_HAS_VALUE(m_deleteTooClose);
  CM_ENSURE_HAS_VALUE(m_deleteTooLowVariance);
  CM_ENSURE_HAS_VALUE(m_imu);
  CM_ENSURE_HAS_VALUE(m_segmentationKind);
  CM_ENSURE_HAS_VALUE(m_skipWindow);
  CM_ENSURE_HAS_VALUE(m_filterKind);
#undef CM_ENSURE_HAS_VALUE

// Check contains valid value
#define CM_CONTAINS(container, value) \
  contains(container.begin(), container.end(), value)

#define CM_ENSURE_CONTAINS(container, dataMember)                           \
  PL_BEGIN_MACRO                                                            \
  if (!CM_CONTAINS(container, dataMember)) {                                \
    CL_THROW_FMT(                                                           \
      "\"{}\" is not a valid option for \"{}\"", *dataMember, #dataMember); \
  }                                                                         \
  PL_END_MACRO

  CM_ENSURE_CONTAINS(skipWindowOptions(), m_skipWindow);
  CM_ENSURE_CONTAINS(deleteTooCloseOptions(), m_deleteTooClose);
  CM_ENSURE_CONTAINS(deleteTooLowVarianceOptions(), m_deleteTooLowVariance);
  CM_ENSURE_CONTAINS(imuOptions(), m_imu);
  CM_ENSURE_CONTAINS(segmentationKindOptions(), m_segmentationKind);
  CM_ENSURE_CONTAINS(windowSizeOptions(), m_windowSize);
  CM_ENSURE_CONTAINS(filterKindOptions(), m_filterKind);

#undef CM_ENSURE_CONTAINS
#undef CM_CONTAINS

  return Configuration{
    *m_skipWindow,
    *m_deleteTooClose,
    *m_deleteTooLowVariance,
    *m_imu,
    *m_segmentationKind,
    *m_windowSize,
    *m_filterKind};
}

const std::array<bool, 2>& Configuration::skipWindowOptions() noexcept
{
  return booleans;
}

const std::array<bool, 2>& Configuration::deleteTooCloseOptions() noexcept
{
  return booleans;
}

const std::array<bool, 2>& Configuration::deleteTooLowVarianceOptions() noexcept
{
  return booleans;
}

const std::array<Imu, 2>& Configuration::imuOptions() noexcept { return imus; }

const std::array<std::string, 3>&
Configuration::segmentationKindOptions() noexcept
{
  static const std::array<std::string, 3> values{{"both", "max", "min"}};
  return values;
}

const std::array<std::size_t, 11>& Configuration::windowSizeOptions() noexcept
{
  static constexpr std::array<std::size_t, 11> values{
    {101, 151, 201, 251, 301, 351, 401, 451, 501, 51, 551}};
  return values;
}

const std::array<std::string, 2>& Configuration::filterKindOptions() noexcept
{
  static const std::array<std::string, 2> values{{"average", "butterworth"}};
  return values;
}

bool Configuration::skipWindow() const noexcept { return m_skipWindow; }

bool Configuration::deleteTooClose() const noexcept { return m_deleteTooClose; }

bool Configuration::deleteTooLowVariance() const noexcept
{
  return m_deleteTooLowVariance;
}

Imu Configuration::imu() const noexcept { return m_imu; }

const std::string& Configuration::segmentationKind() const noexcept
{
  return m_segmentationKind;
}

std::size_t Configuration::windowSize() const noexcept { return m_windowSize; }

const std::string& Configuration::filterKind() const noexcept
{
  return m_filterKind;
}

Configuration::Configuration(
  bool        skipWindow,
  bool        deleteTooClose,
  bool        deleteTooLowVariance,
  Imu         imu,
  std::string segmentationKind,
  std::size_t windowSize,
  std::string filterKind)
  : m_skipWindow{skipWindow}
  , m_deleteTooClose{deleteTooClose}
  , m_deleteTooLowVariance{deleteTooLowVariance}
  , m_imu{imu}
  , m_segmentationKind{std::move(segmentationKind)}
  , m_windowSize{windowSize}
  , m_filterKind{std::move(filterKind)}
{
}
} // namespace cm
