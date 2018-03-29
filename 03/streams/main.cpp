#include <gsl/gsl>

#include "../libstreams/Cypher.h"
#include "../libstreams/DecodedInputStream.h"
#include "../libstreams/EncodedOutputStream.h"
#include "../libstreams/FileInputStream.h"
#include "../libstreams/FileOutputStream.h"
#include <boost/lexical_cast.hpp>
#include <gsl/gsl>
#include <iostream>
#include <vector>

using namespace std;

void Usage()
{
	cout << R"(
usage:  [options] <input-file> <output-file>

options:
	--encrypt <key>. 
	--decrypt <key>.
)";
}

void Process(IInputDataStream& input, IOutputDataStream& output)
{
	constexpr auto BufSize = 128;
	uint8_t buf[BufSize];

	while (!input.IsEOF())
	{
		auto n = input.ReadBlock(buf, BufSize);
		if (n > 0)
		{
			output.WriteBlock(buf, n);
		}
	}
}

constexpr auto EC_ERROR = 2;

using Key = unsigned;
using Keys = std::vector<Key>;

bool ParseKey(const char* s, Key& k)
{
	return boost::conversion::try_lexical_convert(s, k);
}

int Error(const char* msg)
{
	cout << msg << "\n";
	return EC_ERROR;
}

auto ParseKeys(gsl::span<const char*> opts, int nextOpt, const string& option)
{
	Keys keys;

	while (nextOpt < opts.size() - 1)
	{
		Key k = 0;
		if (option == opts[nextOpt] && ParseKey(opts[nextOpt + 1], k))
		{
			keys.push_back(k);
			nextOpt += 2;
		}
		else
		{
			break;
		}
	}

	return make_pair(keys, nextOpt);
}

int main(int argc, char* argv[])
{
	constexpr auto MIN_ARG_COUNT = 3;
	auto args = gsl::make_span(const_cast<const char**>(argv), argc);

	if (args.size() < MIN_ARG_COUNT)
	{
		Usage();
		return EC_ERROR;
	}

	auto options = args.subspan(1, argc - MIN_ARG_COUNT);
	auto nextOpt = 0;

	std::vector<Key> decryptKeys;
	tie(decryptKeys, nextOpt) = ParseKeys(options, nextOpt, "--decrypt");

	std::vector<Key> encryptKeys;
	tie(encryptKeys, nextOpt) = ParseKeys(options, nextOpt, "--encrypt");

	if (nextOpt != options.size())
	{
		return Error("Invalid options");
	}

	IInputDataStreamUniquePtr input = make_unique<FileInputStream>(args[args.size() - 2]);
	for (auto k : decryptKeys)
	{
		input = make_unique<DecodedInputStream>(move(input), GenerateCypher(k));
	}

	IOutputDataStreamUniquePtr output = make_unique<FileOutputStream>(args[args.size() - 1]);
	for (auto k : encryptKeys)
	{
		output = make_unique<EncodedOutputStream>(move(output), CreateCypherForDecoding(GenerateCypher(k)));
	}

	Process(*input, *output);

	return 0;
}
