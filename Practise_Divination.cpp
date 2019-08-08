// Copyleft ! 2019, 向昕哲
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
#include <array>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <sys/timeb.h>
#include <Windows.h>
using std::array;
array<int, 7> divinatorySymbol;
int main(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
	using std::cin;
    using std::cout;
	using std::default_random_engine;
	using std::endl;
	using std::string;
	using std::time;
	using std::uniform_int_distribution;
	array<int, 7>::iterator iter;
    bool ok;
	const int YARROWTOTAL = 55;
	default_random_engine ran;
	int i, j, land, person, remLan, remSky, remTol, sky, yarrowUse;
	string flag, rep;
    struct timeb timeSeed;
	land = 0;
    ok = true;
	person = 0;
	remLan = 0;
	remSky = 0;
	remTol = 0;
    rep = "Y";
	sky = 0;
	yarrowUse = YARROWTOTAL - 6;
	for (iter = divinatorySymbol.begin(); iter != divinatorySymbol.end() - 1; iter++)
	{
		*iter = 0;
	}
    ftime(&timeSeed);
    ran.seed(timeSeed.time * 1000 + timeSeed.millitm);
	cout << "Copyleft ! 2019, 向昕哲" << endl;
	cout << "欢迎使用昕哥牌算卦器，本算卦器由昕哥制作。该软件遵守 GPL v3.0 协议" << endl;
	cout << "本软件只负责算卦，欲查询卦象，请参考周振甫先生译注的《周易译注》（中华书局出版）" << endl;
	cout << "如何查询卦象，请参考：https://ru.qq.com/a/20150814/025103_1.htm" << endl;
	cout << "是否开始算卦（是/Y开始，否/N结束）？";
	cin >> flag;
    while ("是" == rep || "Y" == rep || "y" == rep)
    {
        ok = true;
        while (ok)
        {
            ok = false;
            if ("是" == flag || "Y" == flag || "y" == flag)
            {
                cout << "沐浴斋戒······" << endl;
                cout << "洗手······" << endl;
                cout << "恭敬地开始算卦······" << endl;
                for (i = 0; i < 6; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        uniform_int_distribution<unsigned> uni(1, yarrowUse / 2);
                        sky = uni(ran);
                        while (sky > yarrowUse || sky < 1)
                        {
                            sky = uni(ran);
                        }
                        land = yarrowUse - sky;
                        ++person;
                        --sky;
                        remSky = sky % 4;
                        remLan = land % 4;
                        if (0 == remSky)
                        {
                            remSky = 4;
                        }
                        if (0 == remLan)
                        {
                            remLan = 4;
                        }
                        remTol += remSky + remLan;
                        remTol += person;
                        yarrowUse -= remSky + person + remLan;
                        --person;
                    }
                    divinatorySymbol.at(i) = yarrowUse;
                    remTol = 0;
                    yarrowUse = YARROWTOTAL - 6;
                }
                cout << "结果（从下到上）：";
                for (iter = divinatorySymbol.begin(); iter != divinatorySymbol.end() - 1; iter++)
                {
                    switch (*iter)
                    {
                    case 24:
                        cout << "老阴 ";
                        break;
                    case 28:
                        cout << "少阳 ";
                        break;
                    case 32:
                        cout << "少阴 ";
                        break;
                    case 36:
                        cout << "老阳 ";
                        break;
                    default:
                        break;
                    }
                }
                cout << endl;
                cout << "算卦已结束，是否重新开始（输入是/Y开始，其他字符结束）？";
                cin >> rep;
            }
            else if ("否" == flag || "N" == flag || "n" == flag)
            {
                rep = "N";
            }
            else
            {
                cout << "您输入的不是有效字符，请重新输入：";
                ok = true;
                cin >> flag;
            }
        }
    }
    cout << "按Enter键退出" << endl;
	cin.get();
	cin.get();
	return 0;
}