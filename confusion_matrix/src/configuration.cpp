#include <algorithm>
#include <ostream>
#include <tuple>
#include <utility>

#include <fmt/format.h>
#include <fmt/ostream.h>

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
  const auto contains = [](const auto& container, const auto& value) {
    return ::cm::contains(container.begin(), container.end(), value);
  };

#define CM_ENSURE_CONTAINS(container, dataMember)                           \
  PL_BEGIN_MACRO                                                            \
  if (!contains(container, dataMember)) {                                   \
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

const std::deque<bool>& Configuration::skipWindowOptions() noexcept
{
  static const std::deque<bool> options{false, true};
  return options;
}

const std::deque<bool>& Configuration::deleteTooCloseOptions() noexcept
{
  static const std::deque<bool> options{false, true};
  return options;
}

const std::deque<bool>& Configuration::deleteTooLowVarianceOptions() noexcept
{
  static const std::deque<bool> options{false, true};
  return options;
}

const std::vector<Imu>& Configuration::imuOptions() noexcept
{
  static const std::vector<Imu> options{Imu::Accelerometer, Imu::Gyroscope};
  return options;
}

const std::vector<std::string>&
Configuration::segmentationKindOptions() noexcept
{
  static const std::vector<std::string> values{"both", "max", "min"};
  return values;
}

const std::vector<std::size_t>& Configuration::windowSizeOptions() noexcept
{
  static const std::vector<std::size_t> values{
    101, 151, 201, 251, 301, 351, 401, 451, 501, 51, 551};
  return values;
}

const std::vector<std::string>& Configuration::filterKindOptions() noexcept
{
  static const std::vector<std::string> values{"average", "butterworth"};
  return values;
}

bool operator==(const Configuration& lhs, const Configuration& rhs) noexcept
{
  return std::tie(
           lhs.m_skipWindow,
           lhs.m_deleteTooClose,
           lhs.m_deleteTooLowVariance,
           lhs.m_imu,
           lhs.m_segmentationKind,
           lhs.m_windowSize,
           lhs.m_filterKind)
         == std::tie(
           rhs.m_skipWindow,
           rhs.m_deleteTooClose,
           rhs.m_deleteTooLowVariance,
           rhs.m_imu,
           rhs.m_segmentationKind,
           rhs.m_windowSize,
           rhs.m_filterKind);
}

bool operator!=(const Configuration& lhs, const Configuration& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Configuration& config)
{
  return os << fmt::format(
           "Configuration{{\n"
           "\t\"skipWindow\": {},\n"
           "\t\"deleteTooClose\": {},\n"
           "\t\"deleteTooLowVariance\": {},\n"
           "\t\"imu\": \"{}\",\n"
           "\t\"segmentationKind\": \"{}\",\n"
           "\t\"windowSize\": {},\n"
           "\t\"filterKind\": \"{}\"\n"
           "}}",
           config.m_skipWindow,
           config.m_deleteTooClose,
           config.m_deleteTooLowVariance,
           config.m_imu,
           config.m_segmentationKind,
           config.m_windowSize,
           config.m_filterKind);
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