#include <cstdint>
#include <cstring>

#include <string>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "gtest/gtest.h"

#include "adjust_hardware_timestamp.hpp"

constexpr std::uint64_t overflowThreshold{65532U};

TEST(adjustHardwareTimestamp, shouldDoNothingForNonOverflowedValue)
{
  std::string   value{"0"};
  std::uint64_t count{0};

  fmc::adjustHardwareTimestamp(&value, overflowThreshold, &count);

  EXPECT_EQ("0", value);
  EXPECT_EQ(0, count);
}

TEST(adjustHardwareTimestamp, shouldIncrementOverflowCount)
{
  std::string value1{"65532"};
  std::string value2{"65533"};
  std::string value3{"65534"};
  std::string value4{"65535"};

  std::uint64_t overflowCount{0};

  fmc::adjustHardwareTimestamp(&value1, overflowThreshold, &overflowCount);
  EXPECT_EQ(1, overflowCount);

  fmc::adjustHardwareTimestamp(&value2, overflowThreshold, &overflowCount);
  EXPECT_EQ(2, overflowCount);

  fmc::adjustHardwareTimestamp(&value3, overflowThreshold, &overflowCount);
  EXPECT_EQ(3, overflowCount);

  fmc::adjustHardwareTimestamp(&value4, overflowThreshold, &overflowCount);
  EXPECT_EQ(4, overflowCount);
}

TEST(adjustHardwareTimestamp, shouldWorkForOneRoundOfOverflow)
{
  std::string value1{"0"};
  std::string value2{"1"};
  std::string value3{"2"};
  std::string value4{"3"};
  std::string value5{"4"};
  std::string value6{"5"};

  const std::string value1Expected{"65536"};
  const std::string value2Expected{"65537"};
  const std::string value3Expected{"65538"};
  const std::string value4Expected{"65539"};
  const std::string value5Expected{"65540"};
  const std::string value6Expected{"65541"};

  std::uint64_t overflowCount{1};

  fmc::adjustHardwareTimestamp(&value1, overflowThreshold, &overflowCount);
  ASSERT_EQ(1, overflowCount);
  EXPECT_EQ(value1Expected, value1);

  fmc::adjustHardwareTimestamp(&value2, overflowThreshold, &overflowCount);
  ASSERT_EQ(1, overflowCount);
  EXPECT_EQ(value2Expected, value2);

  fmc::adjustHardwareTimestamp(&value3, overflowThreshold, &overflowCount);
  ASSERT_EQ(1, overflowCount);
  EXPECT_EQ(value3Expected, value3);

  fmc::adjustHardwareTimestamp(&value4, overflowThreshold, &overflowCount);
  ASSERT_EQ(1, overflowCount);
  EXPECT_EQ(value4Expected, value4);

  fmc::adjustHardwareTimestamp(&value5, overflowThreshold, &overflowCount);
  ASSERT_EQ(1, overflowCount);
  EXPECT_EQ(value5Expected, value5);

  fmc::adjustHardwareTimestamp(&value6, overflowThreshold, &overflowCount);
  ASSERT_EQ(1, overflowCount);
  EXPECT_EQ(value6Expected, value6);

  std::string s{"65535"};
  fmc::adjustHardwareTimestamp(&s, overflowThreshold, &overflowCount);
  ASSERT_EQ(2, overflowCount);
  EXPECT_EQ("131071", s);
}

TEST(adjustHardwareTimestamp, shouldWorkForTwoRoundsOfOverflow)
{
  std::string value1{"0"};
  std::string value2{"1"};
  std::string value3{"2"};
  std::string value4{"3"};
  std::string value5{"4"};
  std::string value6{"5"};

  std::uint64_t cnt{2};

  fmc::adjustHardwareTimestamp(&value1, overflowThreshold, &cnt);
  ASSERT_EQ(2, cnt);
  EXPECT_EQ("131072", value1);

  fmc::adjustHardwareTimestamp(&value2, overflowThreshold, &cnt);
  ASSERT_EQ(2, cnt);
  EXPECT_EQ("131073", value2);

  fmc::adjustHardwareTimestamp(&value3, overflowThreshold, &cnt);
  ASSERT_EQ(2, cnt);
  EXPECT_EQ("131074", value3);

  fmc::adjustHardwareTimestamp(&value4, overflowThreshold, &cnt);
  ASSERT_EQ(2, cnt);
  EXPECT_EQ("131075", value4);

  fmc::adjustHardwareTimestamp(&value5, overflowThreshold, &cnt);
  ASSERT_EQ(2, cnt);
  EXPECT_EQ("131076", value5);

  fmc::adjustHardwareTimestamp(&value6, overflowThreshold, &cnt);
  ASSERT_EQ(2, cnt);
  EXPECT_EQ("131077", value6);
}

TEST(adjustHardwareTimestamp, shouldWork)
{
  std::uint64_t           overflowCount{UINT64_C(0)};
  std::uint16_t           sixteenBit{UINT16_C(0)};
  constexpr auto          increment{4};
  constexpr std::uint64_t max{UINT64_C(1048560)};

  for (std::uint64_t i{UINT64_C(0)}; i < max; i += increment) {
    fmt::format_int expected{i};
    fmt::format_int actualFormatter{sixteenBit};
    std::string     s{actualFormatter.str()};
    fmc::adjustHardwareTimestamp(&s, overflowThreshold, &overflowCount);
    ASSERT_EQ(expected.size(), s.size());
    ASSERT_EQ(0, std::memcmp(expected.data(), s.data(), expected.size()));
    sixteenBit += increment;
  }

  ASSERT_EQ(15, overflowCount);
}
