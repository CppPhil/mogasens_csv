require 'rbconfig'
require_relative 'modules/system'
require_relative 'modules/util'
require_relative 'modules/command_line'

MINGW_COMPILER = 'MinGW'.freeze
MSVC_COMPILER = 'MSVC'.freeze

options = CommandLine.parse([CommandLine.compare_segmentation_mode_option, \
                             CommandLine.build_type_option, \
                             CommandLine.compiler_option])

mode = options[:mode]
mode = 'AllDataSets' if mode.nil?

build_type = Util.build_type(options)

compiler = options[:compiler]
compiler = MINGW_COMPILER if compiler.nil?

puts("compare_segmentation.rb: Starting.\n"\
     "mode is \"#{mode}\".\n"\
     "build_type is \"#{build_type}\".\n"\
     "compiler is \"#{compiler}\".")

RESOURCES_DIR = 'resources'.freeze

def compare_segmentation_app(build_type, compiler)
  if System.os == :linux
    './build/compare_segmentation/compare_segmentation_app'
  elsif System.os == :windows
    if compiler == MINGW_COMPILER
      'build/compare_segmentation/compare_segmentation_app.exe'
    elsif compiler == MSVC_COMPILER
      "build/compare_segmentation/#{build_type}/compare_segmentation_app.exe"
    else
      STDERR.puts("Unsupported compiler: \"#{compiler}\", exiting.")
      exit(1)
    end
  else
    STDERR.puts('Unrecognized operating system, exiting.')
    exit(1)
  end
end

run_string = "#{compare_segmentation_app(build_type, compiler)} #{mode}"
unless system(run_string)
  STDERR.puts("Failure running \"#{run_string}\", exiting.")
  exit(1)
end

exit(0)
