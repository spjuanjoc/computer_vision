/**
* @brief Defines the global logger objects.
*
* @author  spjuanjoc
* @date    2021-03-25
*/

#include "Core/Logging/Logger.h"

namespace Logger
{

SpdLogger::SpdLogger()
{
  try
  {
    m_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    m_console_sink->set_level(m_console_level);
    m_console_sink->set_pattern("%Y-%m-%dT%X.%e%z [%^%3!l%$] t[%t]: %v");

    spdlog::set_default_logger(std::make_shared<spdlog::logger>(m_name, spdlog::sinks_init_list({ m_console_sink })));
    spdlog::set_level(spdlog::level::level_enum::debug);
  }
  catch (const spdlog::spdlog_ex& exception)
  {
    fmt::print(stderr, "Log initialization failed: {}\n", exception.what());
  }
}

SpdLogger::~SpdLogger()
{
  spdlog::drop_all();
}

void SpdLogger::setLevel(spdlog::level::level_enum level)
{
  for (auto& sink : spdlog::default_logger()->sinks())
  {
    sink->set_level(level);
  }
}

void
SpdLogger::enableFileSink()
{
  m_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(m_filename, m_max_file_size, m_max_files);

  m_file_sink->set_pattern("%Y-%m-%dT%X.%e%z [%^%3!l%$] t[%t]: %v");
  m_file_sink->set_level(spdlog::level::trace);
  m_file_sink->set_level(m_console_level);

  spdlog::default_logger()->sinks().push_back(m_file_sink);
}

}  // namespace Logger
