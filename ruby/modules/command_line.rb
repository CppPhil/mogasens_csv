require 'optparse'

module CommandLine
  def self.build_type_option
    'build_type'.freeze
  end

  def self.compiler_option
    'compiler'.freeze
  end

  def self.parse(opts)
    options = {}

    OptionParser.new do |opt|
      if opts.include?(build_type_option)
        opt.on('--build_type=BUILD_TYPE', 'Debug | Release') do |o|
          options[:build_type] = o
        end
      end

      mingw_compiler = 'MinGW'.freeze
      msvc_compiler = 'MSVC'.freeze
      compilers = "#{mingw_compiler} | #{msvc_compiler}".freeze

      if opts.include?(compiler_option)
        opt.on('--compiler=COMPILER', compilers) do |o|
          options[:compiler] = o
        end
      end

      opt.on_tail('-h', '--help', 'Show this message') do
        STDERR.puts opt
        exit(0)
      end
    end.parse!

    options
  end
end