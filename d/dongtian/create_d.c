// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <ansi.h>


mapping *dts = ({
/*      
dir:silu
anname:丝绸之路
dtname:火云洞，祝融祠，焚天寺

dir:xihu
anname:雷峰秘道
dtname:剥皮坑，去骨司，怨冢

dir: beijing
anname:天子府
dtname:帝心阁，民心小筑，山河殿

dir:taiwan
anname:日月天
dtname:高山寨，金门境，太鲁阁

dir:kunlun
anname:玉清境
dtname:太元道，天尊塔，鸿蒙间
*/              

                ([
                        "dir" : "emei",
                        "aname" : "峨眉山",
                        "dtname" : ({"凝碧崖", "兜萝绵", "普贤院"}),
                ]),
                ([
                        "dir" : "songshan",
                        "aname" : "嵩山",
                        "dtname" : ({"司马峡", "禅武石", "金刚崖"}),
                ]),
                ([
                        "dir" : "huangshan",
                        "aname" : "黄山",
                        "dtname" : ({"洞观岭", "天莲峰", "梦笔岩"}),
                ]),
                ([
                        "dir" : "huanghe",
                        "aname" : "黄河",
                        "dtname" : ({"黑水洞", "化形潭", "跃龙渊"}),
                ]),
                ([
                        "dir" : "guanwai",
                        "aname" : "长白山",
                        "dtname" : ({"冰雪林", "溯源湖", "封天池"}),
                ]),
                ([
                        "dir" : "yueyang",
                        "aname" : "洞庭湖",
                        "dtname" : ({"怒蛟殿", "水晶宫", "湘竹冢"}),
                ]),

        });

int do_save(string key, mixed val)
{
        mapping dt = ([]);
        string rvl;
        string s;

        if (file_size(__DIR__"dongtian.o")>0) {
                s = read_file(__DIR__"dongtian.o");
                dt = restore_variable(s);
        }

        dt[key] = val;
        rvl = save_variable(dt);
        return write_file(__DIR__"dongtian.o", rvl, 1);
}

mixed do_load(string key)
{
        mapping dt = ([]);
        string s;
        if (file_size(__DIR__"dongtian.o")>0) {
                s = read_file(__DIR__"dongtian.o");
                dt = restore_variable(s);
        }
        return dt[key];
}

int start()
{
        int idx;
        int max = sizeof(dts);
        object room;
        string na, pa, aa, lgmsg;
        
        idx = do_load("idx");
        
        if ( undefinedp(idx) || !idx || idx >= max) idx = 0;
        room = get_object(__DIR__ + dts[idx]["dir"] + "/guangchang");
        na = dts[idx]["dtname"][random(sizeof(dts[idx]["dtname"]))];
        pa = "/d/" + dts[idx]["dir"] + "/";
        aa = dts[idx]["aname"];
        lgmsg = chinese_number(idx + 1) + "号洞天[" + na + "]出现在 " + aa + pa + " 于<" + ctime(time()) + ">";
        //write(HIY + __DIR__ + dts[idx]["dir"] + "/guangchang" + "\n" + na + "\n" + pa + "\n" + aa + "\n" + NOR);
        if (objectp(room)) {
                room->create2(na, pa, aa);
                lgmsg += " 成功.\n";
        } else {
                lgmsg += " 失败！！！\n";
        }
        log_file("static/dongtian", lgmsg);
        do_save("idx", idx + 1);
        
        return 1;
}

string convert_ling(string arg, int level, object target)
{
        string *palist;
        object ob;
        string obfile;
        mapping dt;
        
        if (!arg) return "请输入洞天出现的合法地理范围！，比如：emei\n";
        
        foreach(dt in dts) {
                if (dt["dir"]==arg)
                        break;
                dt = ([]);
        }
        
        if (!sizeof(dt)) return "没有这个范围，或者那里没有洞天会出现。\n";
        
        if (level < 5)
                obfile = __DIR__ + arg + "/lingpai3";
        else if (level < 25)
                obfile = __DIR__ + arg + "/lingpai2";
        else
                obfile = __DIR__ + arg + "/lingpai";
        ob = new(obfile);
        if (ob->move(target)) {
                return "兑换"+dt["aname"]+"范围内的洞天令成功，通行『"+implode(dt["dtname"], "、")+"』。\n";
        } else {
                destruct(ob);
                return "兑换洞天令失败！\n";
        }
}

int is_dongtianarea(string dir)
{
        mapping dt;
        
        foreach(dt in dts) {
                if (dt["dir"]==dir)
                        break;
                dt = ([]);
        }
        
        if (!sizeof(dt)) return 0;
        return 1;
}

//dual "/d/dongtian/create_d.c"->convert_ling("emei",random(125),me)

