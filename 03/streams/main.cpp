#include "../libstreams/FileInputStream.h"
#include "../libstreams/FileOutputStream.h"

using namespace std;

int main()
{
	FileInputStream in(R"(D:\maxim\projects\ood-labs\03\libstreams_tests\test_data\15-byte)");
	FileOutputStream out(R"(D:\maxim\projects\ood-labs\03\libstreams_tests\test_data\15-byte-copy)");

	constexpr auto BufSize = 128;
	uint8_t buf[BufSize];

	while (!in.IsEOF())
	{
		auto n = in.ReadBlock(buf, BufSize);
		if (n > 0)
		{
			out.WriteBlock(buf, n);
		}
	}

	return 0;
}
