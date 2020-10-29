// mapd.c

// #pragma optimize
// #pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

// 标识对应的地名
mapping map_short = ([
        "xiyu"      : "西域",
        //"gaochang"  : "高昌附近",
        "hasake"    : "高昌附近",
        "xingxiu"   : "星宿海",
        "guanwai"   : "关外",
        "yangzhou"  : "扬州",
        "fuzhou"    : "福州",
        "xiangyang" : "襄阳",
        "suzhou"    : "苏州",
        "hangzhou"  : "杭州",
        "xihu"      : "西湖",
        "quanzhou"  : "泉州",
        "lingzhou"  : "灵州",
        "chengdu"   : "成都",
        "jingzhou"  : "荆州",
        "jiaxing"   : "嘉兴",
        "nanyang"   : "南阳",
        "foshan"    : "佛山",
        "dali"      : "大理",
        "changan"   : "长安",
        "hanzhong"  : "汉中",
        "hengyang"  : "衡阳",
        "beijing"   : "北京",
        "shaolin"   : "少林",
        "wudang"    : "武当",
        "emei"      : "峨嵋",
        "qingcheng" : "青城",
        "kunlun"    : "昆仑山",
        "zhongnan"  : "终南山",
        "henshan"   : "衡山",
        "taishan"   : "泰山",
        "huashan"   : "华山",
        "hengshan"  : "恒山",
        "songshan"  : "嵩山",
        "huanghe"   : "黄河",
        "lingjiu"   : "天山",
        "gumu"      : "古墓",
        "meizhuang" : "梅庄",
        "tianlongsi": "天龙寺",
        "xueshan"   : "雪山",
        "taohua"    : "桃花岛",
        "baituo"    : "白驼山",
        "shenlong"  : "神龙岛",
        "yanziwu"   : "燕子坞",
        "village"   : "华山村",
        //"xiakedao"  : "侠客岛",
        "xiaoyao"   : "逍遥林",
        "wanjiegu"  : "万劫谷",
        "xuedao"    : "大雪山",
        "guiyun"    : "归云庄",
        "heimuya"   : "黑木崖",
        "motianya"  : "摩天崖",
        "nanhai"    : "南海之滨",
        "tiezhang"  : "铁掌山",
        "kaifeng"   : "开封",
        "ruzhou"    : "汝州",
        "zhongzhou" : "中州",
        "luoyang"   : "洛阳",
        "lingxiao"  : "凌霄城",
        "lanzhou"   : "兰州",
        "wudujiao"  : "五毒教",
        "kunming"   : "昆明",
        "jueqing"   : "绝情谷",
]);

// 标识对应的地图帮助文件(全部在HELP_DIR中)
mapping map_to = ([
        "xiyu"      : "map_xy",
        "gaochang"  : "map_xy",
        "xingxiu"   : "map_xxh",
        "guanwai"   : "map_gw",
        "yangzhou"  : "map_yz",
        "fuzhou"    : "map_fz",
        "xiangyang" : "map_xi",
        "suzhou"    : "map_sz",
        "hangzhou"  : "map_hz",
        "quanzhou"  : "map_qz",
        "lingzhou"  : "map_lz",
        "chengdu"   : "map_cd",
        "jingzhou"  : "map_jz",
        "jiaxing"   : "map_jx",
        "nanyang"   : "map_ny",
        "foshan"    : "map_fs",
        "dali"      : ({ "map_dl", "map_dls" }),
        "changan"   : "map_ca",
        "hanzhong"  : "map_hanz",
        "hengyang"  : "map_hy",
        "beijing"   : "map_bj",
        "shaolin"   : "map_sl",
        "wudang"    : "map_wd",
        "emei"      : "map_em",
        "qingcheng" : "map_qc",
        "mingjiao"  : "map_kl",
        "quanzhen"  : ({ "map_zn", "map_cyg" }),
        "henshan"   : ({ "map_ss", "map_hy" }),
        "taishan"   : "map_es",
        "huashan"   : "map_ws",
        "hengshan"  : "map_ns",
        "songshan"  : "map_cs",
        "huanghe"   : "map_hh",
        "lingjiu"   : "map_ljg",
        "gumu"      : "map_gm",
        "meizhuang" : "map_mz",
        "tianlongsi": "map_tls",
        "xueshan"   : "map_xss",
        "taohua"    : "map_thd",
        "baituo"    : "map_bts",
        "shenlong"  : "map_sld",
        "yanziwu"   : "map_yzw",
        "village"   : "map_hsc",
        "xiakedao"  : "map_xkd",
        "xiaoyao"   : "map_xyl",
        "wanjiegu"  : "map_wjg",
        "xuedao"    : "map_xdm",
        "guiyun"    : "map_gyz",
        "heimuya"   : "map_hmy",
        "motianya"  : "map_mty",
        "nanhai"    : "map_nh",
        "tiezhang"  : "map_tz",
        "kaifeng"   : "map_kf",
        "ruzhou"    : "map_rz",
        "zhongzhou" : "map_zz",
        "luoyang"   : "map_ly",
        "lingxiao"  : "map_lxg",
        "lanzhou"   : "map_la",
        "wudujiao"  : ({ "map_wdj", "map_dls" }),
        "honghua"   : "map_hhh",
        "kunming"   : "map_km",
        "jueqing"   : "map_jqg",
        "battle1"   : "map_battle1",
]);

// 各地交通联络地
mapping map_trans = ([
        "beijing"   : ([ "name" : "北京",     "room" : "/d/beijing/majiu", ]),
        "yangzhou"  : ([ "name" : "扬州",     "room" : "/d/city/majiu", ]),
        "dali"      : ([ "name" : "大理",     "room" : "/d/dali/majiu", ]),
        "foshan"    : ([ "name" : "佛山",     "room" : "/d/foshan/majiu", ]),
        "fuzhou"    : ([ "name" : "福州",     "room" : "/d/fuzhou/majiu", ]),
        "guanwai"   : ([ "name" : "关外",     "room" : "/d/guanwai/majiu", ]),
        "hangzhou"  : ([ "name" : "杭州",     "room" : "/d/hangzhou/majiu", ]),
        "lanzhou"   : ([ "name" : "兰州",     "room" : "/d/lanzhou/majiu", ]),
        "lingzhou"  : ([ "name" : "灵州",     "room" : "/d/lingzhou/majiu", ]),
        "luoyang"   : ([ "name" : "洛阳",     "room" : "/d/luoyang/majiu", ]),
        "yongdeng"  : ([ "name" : "永登",     "room" : "/d/yongdeng/majiu", ]),
        "suzhou"    : ([ "name" : "苏州",     "room" : "/d/suzhou/majiu", ]),
        "xiangyang" : ([ "name" : "襄阳",     "room" : "/d/xiangyang/majiu", ]),
        "yili"      : ([ "name" : "伊犁",     "room" : "/d/xingxiu/majiu", ]),
        "chengdu"   : ([ "name" : "成都",     "room" : "/d/chengdu/majiu", ]),
        "emei"      : ([ "name" : "峨嵋山",   "room" : "/d/emei/majiu1", ]),
        "emei2"     : ([ "name" : "峨嵋半山", "room" : "/d/emei/majiu2", ]),
        "quanzhou"  : ([ "name" : "泉州",     "room" : "/d/quanzhou/majiu", ]),
        "jiaxing"   : ([ "name" : "嘉兴",     "room" : "/d/jiaxing/majiu", ]),
        "jingzhou"  : ([ "name" : "荆州",     "room" : "/d/jingzhou/majiu", ]),
        "nanyang"   : ([ "name" : "南阳",     "room" : "/d/nanyang/majiu", ]),
        "changan"   : ([ "name" : "长安",     "room" : "/d/changan/majiu", ]),
        "hanzhong"  : ([ "name" : "汉中镇",   "room" : "/d/hanzhong/majiu", ]),
        "hengyang"  : ([ "name" : "衡阳",     "room" : "/d/henshan/majiu", ]),
        "kaifeng"   : ([ "name" : "开封",     "room" : "/d/kaifeng/majiu", ]),
        "kunming"   : ([ "name" : "昆明",     "room" : "/d/kunming/majiu", ]),
        "zhongzhou" : ([ "name" : "中州",     "room" : "/d/zhongzhou/majiu", ]),
]);


// 交通连接
mixed connect_info = ({
        ({ "beijing", "guanwai",        300, }),
        ({ "beijing", "lingzhou",       300, }),
        ({ "beijing", "changan",        200, }),
        ({ "beijing", "xiangyang",      180, }),
        ({ "beijing", "luoyang",        160, }),
        ({ "beijing", "nanyang",        150, }),
        ({ "beijing", "kaifeng",        160, }),
        ({ "beijing", "zhongzhou",      150, }),
        ({ "beijing", "yangzhou",       200, }),
        ({ "lingzhou", "yili",          250, }),
        ({ "lingzhou", "kaifeng",       180, }),
        ({ "lingzhou", "lanzhou",       120, }),
        ({ "lingzhou", "yongdeng",      100, }),
        ({ "lingzhou", "changan",       200, }),
        ({ "luoyang", "kaifeng",        140, }),
        ({ "luoyang", "changan",        100, }),
        ({ "luoyang", "yangzhou",       160, }),
        ({ "luoyang", "xiangyang",      100, }),
        ({ "luoyang", "zhongzhou",      120, }),
        ({ "luoyang", "hanzhong",          80, }),
        ({ "luoyang", "nanyang",        120, }),
        ({ "changan", "yili",           250, }),
        ({ "changan", "lanzhou",        100, }),
        ({ "changan", "hanzhong",          50, }),
        ({ "changan", "xiangyang",      200, }),
        ({ "changan", "nanyang",        200, }),
        ({ "changan", "kaifeng",        160, }),
        ({ "changan", "zhongzhou",      100, }),
        ({ "changan", "chengdu",        250, }),
        ({ "changan", "jingzhou",       230, }),
        ({ "changan", "yangzhou",       260, }),
        ({ "yangzhou", "nanyang",       100, }),
        ({ "yangzhou", "kaifeng",       120, }),
        ({ "yangzhou", "xiangyang",     150, }),
        ({ "yangzhou", "hengyang",      250, }),
        ({ "yangzhou", "suzhou",         80, }),
        ({ "yangzhou", "zhongzhou",      80, }),
        ({ "yangzhou", "hangzhou",      120, }),
        ({ "yangzhou", "jiaxing",       150, }),
        ({ "nanyang", "kaifeng",         50, }),
        ({ "nanyang", "zhongzhou",      120, }),
        ({ "xiangyang", "chengdu",      200, }),
        ({ "xiangyang", "jingzhou",      80, }),
        ({ "xiangyang", "dali",         400, }),
        ({ "xiangyang", "kunming",      500, }),
        ({ "xiangyang", "hengyang",     200, }),
        ({ "xiangyang", "zhongzhou",     80, }),
        ({ "chengdu", "jingzhou",       140, }),
        ({ "chengdu", "kunming",        220, }),
        ({ "chengdu", "emei",           150, }),
        ({ "chengdu", "dali",           300, }),
        ({ "dali",  "jingzhou",         180, }),
        ({ "dali",  "kunming",          150, }),
        ({ "emei",  "kunming",          120, }),
        ({ "emei",  "jingzhou",         140, }),
        ({ "emei",  "emei2",             20, }),
        ({ "hengyang", "foshan",        150, }),
        ({ "suzhou", "hangzhou",         80, }),
        ({ "suzhou", "jiaxing",         120, }),
        ({ "suzhou", "quanzhou",        150, }),
        ({ "suzhou", "zhongzhou",        80, }),
        ({ "hangzhou", "jiaxing",        50, }),
        ({ "hangzhou", "quanzhou",      150, }),
        ({ "hangzhou", "fuzhou",        140, }),
        ({ "lanzhou", "yongdeng",       100, }),
        ({ "lanzhou", "yili",           160, }),
        ({ "jiaxing", "fuzhou",         130, }),
        ({ "jingzhou", "kunming",       140, }),
        ({ "fuzhou", "quanzhou",         30, }),
        ({ "kaifeng", "yongdeng",       110, }),
        ({ "kaifeng", "zhongzhou",      100, }),
});

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path);
// 查看某个地点是否被MAPD所知晓
public int been_known(string outdoors)
{
        return stringp(map_short[outdoors]);
}

// 获得某个户外地点的中文名字
public string query_map_short(string outdoors)
{
        string str;

        if (stringp(str = map_short[outdoors]))
                return str;

        return "不详地点";
}

// 获得所有户外地点的集合
public string *query_all_map_zone()
{
        return keys(map_short);
}

// 获得某个户外地点的地图
public string query_maps(string outdoors)
{
        mixed maps;
        string file;
        string map_result;

        if (undefinedp(maps = map_to[outdoors]))
                return "未有详细地图。\n";

        if (stringp(maps))
        {
                file = HELP_DIR + maps;
                map_result = read_file(file);
                if (! stringp(map_result))
                        map_result = "无法读取地图" + file + "。\n";
                map_result = color_filter(map_result);
                return map_result;
        }

        if (arrayp(maps))
        {
                map_result = "";
                foreach (file in maps)
                {
                        if (file_size(HELP_DIR + file) > 0)
                                map_result += read_file(HELP_DIR + file);
                        else
                                map_result += "无法读取地图" + file + "。\n";
                }
                map_result = color_filter(map_result);
                return map_result;
        }

        error("未知错误。\n");
}

// 获得地图中某一行的第x开始的n个字符，其中地图行中@打头的字
// 符及后续字符一概认为不占地方。比如"@B123@E"，则第二个字符
// 是'2'，而不是B。如果n为-1，则返回一直到末尾的所有字符
//
// 这样存在问题，有必要引入一个变量， 标识是否取回颜色，不过
// 由于出错的几率相当小，所以姑且不计。
string get_map_line(string line, int x, int n)
{
        string rs;

        rs = "";
        if (n == 0)
                return rs;

        // 找到相应的位置
        while (x)
        {
                if (strlen(line) == 0)
                        // 字符串长度不够
                        return rs;

                if (line[0] == '@')
                {
                        if (strlen(line) >= 2)
                                // 去掉@和后续的字符
                                line = line[2..<1];
                        else
                                // 长度不够？返回空字符串
                                return rs;
                } else
                {
                        // 字符串去掉第一个字符，相当于向右移动
                        x--;
                        line = line[1..<1];
                }
        }

        // 截取n个字符
        // 为什么这里用do-while，而不直接用while？这是有原因
        // 的。
        rs = "";
        for (;;)
        {
                if (strlen(line) == 0)
                        // 已经无字符可取
                        return rs;

                if (line[0] == '@')
                {
                        if (strlen(line) >= 2)
                        {
                                rs += line[0..1];
                                line = line[2..<1];
                        } else
                        {
                                rs += line;
                                return rs;
                        }
                } else
                {
                        if (n == 0) break; // 结束截取
                        n--;
                        rs += line[0..0];
                        line = line[1..<1];
                        continue;
                }
        }
        return rs;
}

// 为地点标记颜色：名字必须为中文
// 标记的时候一行行扫描，扫描的同时打标记，将标记设置为@B和
// @E，如果扫描成功就把@B和@E替换成为@R和@N，否则就去掉这些
// 临时标记。
// 最后将将所有的标记替换成颜色：@R->WHT @N->NOR
public string mark_map(string map, string name)
{
        string *lines;
        string temp;
        string rs;
        int i;
        int x, y, xd;           // 比较的地图位置
        int n;

        // 去除地图的颜色：这样可以准确的判断绝对的坐标
        map = filter_color(map);

        // 将地图分成行
        lines = explode(map, "\n");
        for (i = 0; i < sizeof(lines); i++)
        {
                if (strsrch(lines[i], name[0..1]) == -1)
                        // 本行不存在名称的第一个汉字，继续，继续下一行
                        continue;

                x = 0;
                temp = replace_string(lines[i], "@R", "");
                temp = replace_string(temp, "@N", "");
                while (x < strlen(temp) - 1)
                {
                        xd = strsrch(temp[x..<1], name[0..1]);
                        if (xd == -1)
                                // 本行后续没有名称的第一个汉字，继续下一行
                                break;

                        // 该行匹配上了第一个汉字：比较后续的汉字，
                        // 首先横向比较，因此不断移动xd，如果横向扫
                        // 描不到，就往纵向比较，变化y。
                        x += xd;
                        y = i;
                        xd = 2;
                        rs = get_map_line(lines[y], 0, x);
                        rs += "@B";
                        rs += get_map_line(lines[y], x, 2);
                        for (n = 2; n < strlen(name); n += 2, xd += 2)
                        {
                                // 首先横向比较
                                if (x + xd + 2 <= strlen(lines[y]) &&
                                    get_map_line(lines[y], x + xd, 2) == name[n..n + 1])
                                {
                                        // 横向比较到了，继续横向比较
                                        rs += name[n..n + 1];
                                        continue;
                                }

                                // 横向比较失败了，横向还原对齐，纵向比较
                                rs += "@E" + get_map_line(lines[y], x + xd, -1);
                                xd = 0;
                                y++;
                                if (y < sizeof(lines) &&
                                    x + 2 <= strlen(lines[y]) &&
                                    get_map_line(lines[y], x, 2) == name[n..n + 1])
                                {
                                        // 纵向比较到了，继续横向比较
                                        lines[y - 1] = rs;
                                        rs = get_map_line(lines[y], 0, x);
                                        rs += "@B";
                                        rs += name[n..n + 1];
                                        continue;
                                }

                                // 比较失败，不在(x, i)这个位置
                                y--;
                                while (y >= i)
                                {
                                        // 恢复原先的地图，去掉标记
                                        lines[y] = replace_string(lines[y], "@B", "");
                                        lines[y] = replace_string(lines[y], "@E", "");
                                        y--;
                                }
                                break;
                        }

                        if (n >= strlen(name))
                        {
                                // 匹配成功
                                rs += "@E" + get_map_line(lines[y], x + xd, -1);
                                lines[y] = rs;
                                while (y >= i)
                                {
                                        // 将标记设置为正常标记
                                        lines[y] = replace_string(lines[y], "@B", "@R");
                                        lines[y] = replace_string(lines[y], "@E", "@N");
                                        y--;
                                }
                        }

                        // 移动x，继续匹配
                        x++;
                }
                // 扫描完毕一行，继续扫描下一行
        }
        // 处理完毕

        return implode(lines, "\n") + "\n";
}

// 获得所在某个地点的地图并标记当前所在的位置
public string marked_map(object env)
{
        mixed maps;
        string file;
        string outdoors;
        string map_result;
        int result_ok;

        if (! objectp(env))
                return "这里无法获得地图。\n";

        if( !stringp(outdoors=query("outdoors", env)) )
                return "必须在室外察看所处的具体位置。\n";

        if (undefinedp(maps = map_to[outdoors]))
                return "未有详细地图。\n";

        if (stringp(maps))
        {
                file = HELP_DIR + maps;
                map_result = read_file(file);
                if (! stringp(map_result))
                        map_result = "无法读取地图" + file + "。\n";
                map_result = color_filter(map_result);
                map_result = mark_map(map_result, env->short());
        } else
        if (arrayp(maps))
        {
                map_result = "";
                result_ok = 0;
                foreach (file in maps)
                {
                        if (file_size(HELP_DIR + file) > 0)
                                map_result = read_file(HELP_DIR + file);
                        else
                        {
                                map_result = "无法读取地图" + file + "。\n";
                                result_ok = 1;
                                break;
                        }

                        map_result = color_filter(map_result);
                        map_result = mark_map(map_result, env->short());
                        if (strsrch(map_result, "@R") != -1)
                        {
                                result_ok = 1;
                                break;
                        }
                }
                // 所有的地图都没有变化？取第一个
                if (! result_ok)
                {
                        map_result = read_file(HELP_DIR + maps[0]);
                        map_result = color_filter(map_result);
                }
        } else
                error("未知错误。\n");

        map_result = replace_string(map_result, "@R", HIC);
        map_result = replace_string(map_result, "@N", NOR);
        return map_result;
}

// 玩家纪录传闻
public int record_rumor(mixed obs, string topic, mixed event_ob)
{
        object ob;
        string title;
        int n;

        if (objectp(obs)) obs = ({ obs }); else
        if (! arrayp(obs)) return 0;

        if (! stringp(title = event_ob->query_detail(topic)))
                return 0;

        if (stringp(event_ob)) event_ob = base_name(find_object(event_ob)); else
                               event_ob = base_name(event_ob);
        n = 0;
        foreach (ob in obs)
        {
                if( !playerp(ob) || !query("out_family", ob))continue;
                if( query("rumor/"+topic, ob))continue;
                set("rumor/"+topic, event_ob, ob);
                message("vision", "你掏出地图册，翻到最后面，写下了有关『" +
                                  topic + "』的记录。\n", ob);
                n++;
        }

        return n;
}

// 获得某个交通地点的信息
public varargs mixed query_trans_info(string to)
{
        if (! stringp(to))
                return map_trans;

        return map_trans[to];
}

// 获得交通连接信息
public mapping query_connect_info()
{
        return connect_info;
}

string make_color(string map)
{
        map = replace_string(map, "★", HIR"★"NOR);
        map = replace_string(map, "≈", HIC"≈"NOR);
        map = replace_string(map, "～", HIC"～"NOR);
        map = replace_string(map, "∧", HIG"∧"NOR);
        map = replace_string(map, "ψ", GRN"ψ"NOR);
        map = replace_string(map, "♀", HIR"♀"NOR);
        map = replace_string(map, "±", HIM"±"NOR);
        map = replace_string(map, "＋", HIG"＋"NOR);
        map = replace_string(map, "∴", YEL"∴"NOR);
        map = replace_string(map, "∷", YEL"∷"NOR);
        map = replace_string(map, "≌", HIW"≌"NOR);
        map = replace_string(map, "＊", MAG"＊"NOR);
        map = replace_string(map, "—", HIY"—"NOR);
        map = replace_string(map, "｜", HIY"｜"NOR);
        map = replace_string(map, "＼", HIY"＼"NOR);
        map = replace_string(map, "／", HIY"／"NOR);
        map = replace_string(map, "↑", HIY"↑"NOR);
        map = replace_string(map, "↓", HIY"↓"NOR);
        map = replace_string(map, "→", HIY"→"NOR);
        map = replace_string(map, "←", HIY"←"NOR);
        map = replace_string(map, "--", HIY"--"NOR);
        map = replace_string(map, "│", HIY"│"NOR);
        map = replace_string(map, "┼", HIY"┼"NOR);
        map = replace_string(map, "┌", HIY"┌"NOR);
        map = replace_string(map, "┐", HIY"┐"NOR);
        map = replace_string(map, "└", HIY"└"NOR);
        map = replace_string(map, "┘", HIY"┘"NOR);
        map = replace_string(map, "┬", HIY"┬"NOR);
        map = replace_string(map, "┴", HIY"┴"NOR);
        map = replace_string(map, "├", HIY"├"NOR);
        map = replace_string(map, "┤", HIY"┤"NOR);
        map = replace_string(map, "-", HIY"-"NOR);
        map = replace_string(map, "~", HIC"~"NOR);
        map = replace_string(map, "|", HIC"|"NOR);
        map = replace_string(map, "@", HIW"@"NOR);
        map = replace_string(map, "*", GRN"@"NOR);
        map = replace_string(map, "<", HIG"<");
        map = replace_string(map, ">", ">"NOR);
        map = replace_string(map, "【", YEL"【");
        map = replace_string(map, "】", "】"NOR);
        map = replace_string(map, "〖", CYN"〖"NOR);
        map = replace_string(map, "〗", CYN"〗"NOR);
        return map;
}

string *dirs = ({
        "north",
        "south",
        "east",
        "west",
        "northup",
        "southup",
        "eastup",
        "westup",
        "northdown",
        "southdown",
        "eastdown",
        "westdown",
        "northeast",
        "northwest",
        "southeast",
        "southwest",
        "up",
        "down",
        "enter",
        "out",
});

public string show_map(object env)
{
        int i, j, jj = 0, k, kk = 0;
        string file,map,name,dest,*search;
        mapping exit1, exit2, exit3;
        object room1, room2, room3, room4;

        if( !(file=query("region", env)) && !(file=query("outdoors", env)) )
        {
                if( mapp(exit1=query("exits", env)) )
                {
                        for (i=0; i<sizeof(dirs); i++)
                        {
                                if(dest = exit1[dirs[i]])
                                {
                                        if(!(room2 = find_object(dest)))
                                                room2=load_object(dest);
                                        if( file=query("outdoors", room2) )
                                                break;
                                        else
                                        {
                                                if( mapp(exit2=query("exits", room2)) )
                                                {
                                                        for (j=0; j<sizeof(dirs); j++)
                                                        {
                                                                if(dest = exit2[dirs[j]])
                                                                {
                                                                        if(!( room3 = find_object(dest)) )
                                                                                room3 = load_object(dest);
                                                                        if( file=query("outdoors", room3) )
                                                                        {
                                                                                jj = 1;
                                                                                break;
                                                                        }
                                                                        else
                                                                        if( mapp(exit3=query("exits", room3)) )
                                                                        {
                                                                                for (k=0; k<sizeof(dirs); k++)
                                                                                {
                                                                                        if(dest = exit3[dirs[k]])
                                                                                        {
                                                                                                if(!( room4 = find_object(dest)) )
                                                                                                        room4 = load_object(dest);
                                                                                                if( file=query("outdoors", room4) )
                                                                                                {
                                                                                                        kk = 1;
                                                                                                        break;
                                                                                                }
                                                                                        }
                                                                                }
                                                                        }
                                                                        if (kk == 1)
                                                                        {
                                                                                jj = 1;
                                                                                break;
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                        if (jj == 1) break;
                                }
                        }
                }
                if (i==sizeof(dirs))
                        return HIG"这里不能查看地图，请到室外。\n"NOR;
        }
        if( !stringp(file) || !sizeof(file) ) return HIY"暂时还没有开放这里的地图查询。\n"NOR;
        name = filter_color(query("short", env));
        if( strsrch(file, "_zone") != -1 )
                sscanf(file, "%s_zone", file);
        if( file_size("/doc/map/" + file)>0 )
        {
                if(stringp(map = read_file("/doc/map/" + file)))
                {
                        //map = make_color(map);
                        map = replace_string(map, name, HBBLU+HIG+name+NOR);
                        return map;
                }
        }
        return HIY"暂时还没有开放这里的地图查询。\n"NOR;
}

/********************************************************************/
#define LINE HIM "------------------------------------------------------------------------------------------" NOR
#define LINE_COUNT 4

mapping trans = ([
        // 城市
        "beijing"   : "/d/beijing/tiananmen",
        "yangzhou"  : "/d/city/guangchang",
        "gc"        : "/d/city/guangchang",
        "chengdu"   : "/d/chengdu/guangchang",
        "changan"   : "/d/changan/bridge2",
        "luoyang"   : "/d/luoyang/center",
        "suzhou"    : "/d/suzhou/canlangting",
        "hangzhou"  : "/d/hangzhou/road10",
        "hanzhong"  : "/d/hanzhong/zhongxin",
        "fuzhou"    : "/d/fuzhou/dongjiekou",
        "foshan"    : "/d/foshan/street3",
        "dali"      : "/d/dali/center",
        "nanyang"   : "/d/nanyang/nanyang",
        "ruzhou"    : "/d/ruzhou/ruzhou",
        "guanwai"   : "/d/guanwai/jishi",
        "lanzhou"   : "/d/lanzhou/square",
        "yongdeng"  : "/d/yongdeng/yongdeng",
        "lingzhou"  : "/d/lingzhou/center",
        "xiangyang" : "/d/xiangyang/guangchang",
        "quanzhou"  : "/d/quanzhou/guangchang",
        "jiaxing"   : "/d/jiaxing/jiaxing",
        "jingzhou"  : "/d/jingzhou/guangchang",
        "emei2"     : "/d/emei/majiu1",
        "zhongnan"  : "/d/quanzhen/shanjiao",
        "henyang"   : "/d/henshan/hengyang",
        "hengyang"  : "/d/henshan/hengyang",
        "kaifeng"   : "/d/kaifeng/zhuque",
        "kunming"   : "/d/kunming/jinrilou",
        "zhongzhou" : "/d/zhongzhou/shizhongxin",
        "wuxi"      : "/d/wuxi/guangchang", // 无锡
        "juyong"    : "/d/changcheng/juyongguan",  //居庸关
        "jiayu"     : "/d/xingxiu/jiayuguan",  //嘉峪关
        "huibu"     : "/d/huijiang/buluo1", //回疆 回部部落
        "xinjiang"  : "/d/huijiang/caoyuan", //新疆  大草原
        "yili"      : "/d/xingxiu/yili", //伊犁城
        "yueyang"   : "/d/yueyang/zhongxin", //岳阳城
        "yanping"   : "/d/yanping/fuqiao1", //延平府

        // 门派
        "songshan"  : "/d/songshan/dadian",
        "henshan"   : "/d/henshan/zhurongdian",
        "guiyun"    : "/d/yixing/taihu",
        "taohua"    : "/d/taohua/jingshe",
        "gaibang"   : "/d/gaibang/inhole",
        "tiezhang"  : "/d/tiezhang/guangchang",
        "honghua"   : "/d/huijiang/damen",
        "wudu"      : "/d/wudu/damen",
        "meizhuang" : "/d/meizhuang/keting",
        "lingxiao"  : "/d/lingxiao/bar",
        "jueqing"   : "/d/jueqing/shanzhuang",
        "heimuya"   : "/d/heimuya/up1",
        "taishan"   : "/d/taishan/taishanjiao",
        "xingxiu"   : "/d/xingxiu/xxh1",
        "ouyang"    : "/d/baituo/guangchang",
        "baituo"    : "/d/baituo/guangchang",
        "quanzhen"  : "/d/quanzhen/damen",
        "gumu"      : "/d/gumu/mumen",
        "lingjiu"   : "/d/lingjiu/jian",
        "shaolin"   : "/d/shaolin/shanmen",
        "wudang"    : "/d/wudang/jiejianyan",
        "xiaoyao"   : "/d/xiaoyao/xiaodao4",
        "huashan"   : "/d/huashan/shaluo",
        "xueshan"   : "/d/xuedao/nroad4",
        "xuedao"    : "/d/xuedao/wangyougu",
        "kunlun"    : "/d/kunlun/klshanlu",
        "qingcheng" : "/d/qingcheng/tianshidong",
        "emei"      : "/d/emei/huayanding",
        "mingjiao"  : "/d/mingjiao/shanjiao",
        "mojiao"    : "/d/yuanyue/damen",
        "murong"    : "/d/yanziwu/bozhou",
        "tang"      : "/d/tangmen/tmyizhan",
        "tangmen"   : "/d/tangmen/tmyizhan",
        "miao"      : "/d/zhongzhou/miaojia_houting",
        "hu"        : "/d/guanwai/xiaoyuan",
        "duan"      : "/d/dali/neitang",

        // 常用
        "kedian"    : "/d/city/kedian",
        "wumiao"    : "/d/city/wumiao",
        "guofu"     : "/d/wuguan/guofu_gate",///
        "ganjiang"  : "/d/item/xiaowu",
        "tianshi"   : "/d/item/road1",
        "haigui"    : "/d/xiakedao/xkroad5",
        "shendiao"  : "/d/huashan/jianzhong",
        "luban"     : "/d/room/xiaoyuan",
        "dugu"      : "/d/huashan/shandong",
        "huang"     : "/d/dali/lushui",
        "shenni"    : "/d/xiakedao/zhuwu2",
        "kuihua"    : "/d/beijing/shanlu3",
        "nanhai"    : "/d/xiakedao/haibin",
        "wenmiao"   : "/d/luoyang/wenmiao",
]);

mapping show_trans_info = ([
        // 城市
        "beijing"   : ({ "北京", "city" }),
        "luoyang"   : ({ "洛阳", "city" }),
        "yangzhou"  : ({ "扬州", "city" }),
        "dali"      : ({ "大理", "city" }),
        "foshan"    : ({ "佛山", "city" }),
        "fuzhou"    : ({ "福州", "city" }),
        "guanwai"   : ({ "关外", "city" }),
        "hangzhou"  : ({ "杭州", "city" }),
        "lanzhou"   : ({ "兰州", "city" }),
        "lingzhou"  : ({ "灵州", "city" }),
        "yongdeng"  : ({ "永登", "city" }),
        "suzhou"    : ({ "苏州", "city" }),
        "xiangyang" : ({ "襄阳", "city" }),
        "yili"      : ({ "伊犁", "city" }),
        "chengdu"   : ({ "成都", "city" }),
        "emei2"     : ({ "峨嵋山", "city" }),
        "zhongnan"  : ({ "终南山", "city" }),
        "quanzhou"  : ({ "泉州", "city" }),
        "jiaxing"   : ({ "嘉兴", "city" }),
        "jingzhou"  : ({ "荆州", "city" }),
        "nanyang"   : ({ "南阳", "city" }),
        "ruzhou"    : ({ "汝州", "city" }),
        "changan"   : ({ "长安", "city" }),
        "hanzhong"  : ({ "汉中", "city" }),
        "hengyang"  : ({ "衡阳", "city" }),
        "kaifeng"   : ({ "开封", "city" }),
        "kunming"   : ({ "昆明", "city" }),
        "zhongzhou" : ({ "中州", "city" }),
        "wuxi"      : ({ "无锡", "city" }),
        "yueyang"   : ({ "岳阳", "city" }),
        "yanping"   : ({ "延平", "city" }),
        "juyong"    : ({ "居庸关", "city" }),
        "jiayu"     : ({ "嘉峪关", "city" }),
        "huibu"     : ({ "回疆", "city" }),
        "xinjiang"  : ({ "新疆", "city" }),

        // 门派
        "huashan"   : ({ "华山派", "family" }),
        "xuedao"    : ({ "血刀门", "family" }),
        "songshan"  : ({ "嵩山派", "family" }),
        "xueshan"   : ({ "雪山派", "family" }),
        "henshan"   : ({ "衡山派", "family" }),
        "gaibang"   : ({ "丐帮", "family" }),
        "shaolin"   : ({ "少林派", "family" }),
        "tiezhang"  : ({ "铁掌帮", "family" }),
        "wudang"    : ({ "武当派", "family" }),
        "honghua"   : ({ "红花会", "family" }),
        "emei"      : ({ "峨嵋派", "family" }),
        "wudu"      : ({ "五毒教", "family" }),
        "xiaoyao"   : ({ "逍遥派", "family" }),
        "mingjiao"  : ({ "明教", "family" }),
        "lingjiu"   : ({ "灵鹫宫", "family" }),
        "xuanming"  : ({ "玄冥谷", "family" }),
        "xingxiu"   : ({ "星宿派", "family" }),
        "meizhuang" : ({ "梅庄", "family" }),
        "gumu"      : ({ "古墓派", "family" }),
        "lingxiao"  : ({ "雪山剑派", "family" }),
        "quanzhen"  : ({ "全真派", "family" }),
        "mojiao"    : ({ "魔教", "family" }),
        "kunlun"    : ({ "昆仑派", "family" }),
        "qingcheng" : ({ "青城派", "family" }),
        "jueqing"   : ({ "绝情谷", "family" }),
        "guiyun"    : ({ "归云庄", "family" }),
        "taohua"    : ({ "桃花岛", "family" }),
        "heimuya"   : ({ "日月神教", "family" }),
        "ouyang"    : ({ "欧阳世家", "family" }),
        "miao"      : ({ "中原苗家", "family" }),
        "murong"    : ({ "慕容世家", "family" }),
        "hu"        : ({ "关外胡家", "family" }),
        "duan"      : ({ "大理段氏", "family" }),
        "tang"      : ({ "唐门世家", "family" }),

        // 常用
        "kedian"    : ({ "扬州客店", "common" }),
        "wumiao"    : ({ "武庙", "common" }),
        "guofu"     : ({ "郭府外", "common" }),///d/wuguan/guofu_gate
        "ganjiang"  : ({ "干将莫邪", "common" }),
        "tianshi"   : ({ "张天师", "common" }),
        "haigui"    : ({ "海龟", "common" }),
        "shendiao"  : ({ "神雕", "common" }),
        "luban"     : ({ "鲁班", "common" }),
        "dugu"      : ({ "独孤求败", "common" }),
        "huang"     : ({ "黄裳", "common" }),
        "shenni"    : ({ "南海神尼", "common" }),
        "kuihua"    : ({ "葵花太监", "common" }),
        "nanhai"    : ({ "南海", "common" }),
        "wenmiao"   : ({ "文庙", "common" }),
]);

string g_show_trans;

mapping get_trans2()
{
        mapping m;
        string *keys_show_trans;
        int i;

        m = ([]);
        keys_show_trans = keys(show_trans_info);

        for (i = 0; i < sizeof(keys_show_trans); i ++)
        {
                m += ([ show_trans_info[keys_show_trans[i]][0] : keys_show_trans[i] ]);
        }

        return m;
}

mapping show_trans2 = get_trans2();

string get_trans_path(string s)
{
        string st;

        // 同时兼容中文和英文
        if (member_array(s, keys(trans)) == -1)
        {
                s = show_trans2[s];
        }

        return trans[s];
}

int show_trans(object me)
{
        mapping self_flag;
        int i;
        string *places, show_places;
        string show_city, show_family, show_comm;
        int ncity, nfamily, ncomm;

        show_places = "";
        show_city = "";
        show_family = "";
        show_comm = "";

        if (sizeof(g_show_trans))
        {
                show_places += g_show_trans;
        }
        else
        {

                show_places += HIY "【你可以骑马到以下地方】\n" + LINE + "\n"NOR;

                places = keys(show_trans_info);
                places = sort_array(places, 1);
                for (i = 0; i < sizeof(places); i ++)
                {
                        if( show_trans_info[places[i]][1] == "common" )
                        {
                                show_comm += sprintf("%-10s: %-12s", places[i], show_trans_info[places[i]][0]);
                                ncomm ++;
                                if (ncomm % LINE_COUNT == 0)show_comm += "\n";
                        }
                        else if( show_trans_info[places[i]][1] == "family" )
                        {
                                show_family += sprintf("%-10s: %-12s", places[i], show_trans_info[places[i]][0]);
                                nfamily ++;
                                if (nfamily % LINE_COUNT == 0)show_family += "\n";
                        }
                        else
                        {
                                show_city += sprintf("%-10s: %-12s", places[i], show_trans_info[places[i]][0]);
                                ncity ++;
                                if (ncity % LINE_COUNT == 0)show_city += "\n";
                        }
                }
                show_places += HIG + "<城市>\n" NOR;
                show_places += show_city;
                show_places += HIY + "\n<门派>\n" NOR;
                show_places += show_family;
                show_places += HIC + "\n<常用>\n" NOR;
                show_places += show_comm;

                g_show_trans = show_places; // 全局记录，不需要每次都计算
        }

        // 自己记录的地点
        self_flag=query("horse/flags", me);

        if (mapp(self_flag))
        {
                show_places += HIR "\n<用户记录地点>\n" NOR;
                if (sizeof(self_flag))
                {
                        places = keys(self_flag);
                        for (i = 0; i < sizeof(places); i ++)
                        {
                                if( file_size(self_flag[places[i]]+".c") < 0 ) continue;
                                show_places += sprintf("%-10s: %-12s", places[i], get_object(self_flag[places[i]])->short());
                                if ((i+1) % LINE_COUNT == 0)show_places += "\n";
                        }
                        if (sizeof(places) % LINE_COUNT != 0)show_places += "\n";
                }
        }
        else
        {
                show_places += "\n";
        }

        show_places += LINE + HIY "\n请使用 rideto <目的地> 骑马到指定地方，例如：rideto 客店\n" NOR;

        write(show_places);
        return 1;
}

// 骑马到指定地点
int move_to(object me, string place)
{
        object running, horse, follower;
        string trans_path;
        int trans_times, sk_riding, level;
        string temp,temp2;
        object trans_target, me_env;

        // 检查是否骑马
        if( !objectp(horse=query_temp("is_riding", me)) )
        {
                write("你并没有骑马啊。\n" );
                return 1;
        }
        if( query_temp("running", horse) )
        {
                write(horse->name() + NOR "正在奔跑呢！\n" NOR);
                return 1;
        }
        if( query_temp("running", me) )
        {
                write("你正在奔跑中呢。\n");
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
        {
                write("你正忙呢！\n");
                return 1;
        }

        sk_riding = me->query_skill("riding", 1);
        if( sk_riding < 1 ) sk_riding = 1;
        /*
        if (sk_riding < 30)
        {
                write("你骑术不够，无法骑马到指定地点。\n");
                return 1;
        }
        */

        // 检查是否有该地方可去
        if (! stringp(trans_path = get_trans_path(place)))
        {
                if( !stringp(trans_path=query("horse/flags/"+place, me)) )
                {
                        write("你无法骑马达到这个地方。\n");
                        return 1;
                }
                if (! find_object(trans_path) && ! load_object(trans_path))
                {
                        write("你无法骑马达到这个地方。\n");
                        return 1;
                }
        }

        // 某些地方无法骑马到达
        trans_target = find_object(trans_path);
        if (! objectp(trans_target))trans_target = load_object(trans_path);

        if (! objectp(trans_target))
        {
                write("你无法骑马达到这个地方。\n");
                return 1;
        }

        if( query("no_magic", trans_target) || query("no_rideto", trans_target) || query("no_flyto", trans_target) )
        {
                write("你无法骑马达到这个地方。\n");
                return 1;
        }

/*
        // 修改为从源头封堵
        if (sscanf(base_name(trans_target), "/d/city2/%*s") ||
            sscanf(base_name(trans_target), "/data/%*s") ||
            sscanf(base_name(trans_target), "/f/%*s") ||
            sscanf(base_name(trans_target), "/maze/%*s") )
        {
                write("你无法骑马达到这个地方。\n");
                return 1;
        }
*/

        me_env = environment(me);

        /*
        // rideto已经判断了
        if( query("no_magic", me_env) || query("no_rideto", me_env) || query("no_flyto", me_env) )
        {
                write("此处不能骑马。\n");
                return 1;
        }

        // dream_boat上无法骑马
        if (sscanf(base_name(me_env), "/clone/misc/dream_%s", temp) == 1)
        {
                write("此处无法骑马。\n");
                return 1;
        }
        */

/*
        // 玩家房间无法到达，自己的房间可以
        if (sscanf(trans_path, "/data/room/%s/%s", temp, temp2) == 2)
        {
                // 自己房间可以进入
                if( query("id", me) != temp )
                {
                        write("你无法骑马进入私人住宅。\n");
                        return 1;
                }
        }

        if (sscanf(trans_path, "/clone/misc/dream_%s", temp) == 1)
        {
                write("你无法骑马达到这个地方。\n");
                return 1;
        }
*/

        if( trans_target == me_env )
        {
                write("你已经在这里了。\n");
                return 1;
        }

        /*
        level = query("level", horse); // 最高100
        trans_times = 2 + random(1 + 300 / sk_riding) + (10 - (level/10)*3);
        if( trans_times > 1 ) trans_times = 1;
        if( trans_times < 0 ) trans_times = 0;
        */

        message("vision",  "\n" + horse ->name() + HIW "一声长"
                  "嘶，箭一般地冲出 ……\n" NOR, environment(me), ({horse}));

        running = new("/clone/misc/running");
        me->move(running);
        if( objectp(follower=query_temp("is_rided_follow", horse)) )
        {
                if (environment(follower) && (interactive(follower) || ! userp(follower)))
                        follower->move(running);
        }

        set_temp("running", 1,  horse);
        set_temp("running", 1,  me);

        if( !trans_times ) arrived_dest(me, follower, running, horse, trans_path); else
        //call_out("arrived_dest", trans_times, me, follower, running, horse, trans_path);
        arrived_dest(me, follower, running, horse, trans_path);

        return 1;
}

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path)
{
        object ob, ob2;

        if (! objectp(me)) return 0;
        if (objectp(horse))
                tell_object(me, "\n" + horse->name() + HIW "到了目的地，长嘶一声，猛然停下，顿时尘土四散……\n" NOR);
        //if (objectp(me))
        //{
                me->move(trans_path);
                delete_temp("running",  me);
                if (random(2))me->improve_skill("riding", 1);
        //}
        if (objectp(follower))follower->move(trans_path);
        if( objectp(horse))delete_temp("running", horse);

        if(objectp(running))destruct(running);

        if (objectp(horse))
                message("vision",  "\n" + this_object()->name() + HIW "到了目的地，长嘶一声，猛然"
                        "停下，顿时尘土四散……\n" NOR, environment(horse), ({me, horse}));

        // 到达地点后下马
        /*
        "/cmds/std/unride"->main(me);
        horse->set_leader(me);
        */

        return 1;
}

// 强行上马
int me_ride(object me, object horse)
{
        object owner;

        if( !objectp(me) || !objectp(horse) )
        {
                write("物件出错。\n");
                return 0;
        }

        if( query_temp("is_rided_follow", horse) )
                return 0;

        owner = query_temp("is_rided_by", horse);

        set_temp("is_rided_follow", me, horse);
        set_temp("is_riding_follow", horse, me);

        message_vision("$N跃上$n" NOR "，坐在" + owner->name() + "的身后。\n", me, horse);

        return 1;
}
