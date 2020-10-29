#include <room.h>
#include <ansi.h>
#include <getconfig.h>
inherit ROOM;

#define HEIDIAN "xiyu"
#define HEIDIAN_NAME "西域黑店"

int do_look(string arg);

void create()
{
    set("short", HIY"金色走廊"NOR);
        set("long", @LONG
这里是一条金碧辉煌的走廊，前面通往拍卖休息室，墙壁上画着
一块黑底金字的大匾(dabian)，整个走廊静谧严肃，令人不敢大声喧
哗。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "south"  : "/d/city/pm_road6",
        "north"  : "/d/city/pm_road8",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_look","look");
}

int do_look(string arg)
{
    int i;
    object pms;
    string msg;
    mapping *heidian_record;

    if (arg != "dabian") return 0;
    pms = load_object("/adm/npc/fjtx");
    heidian_record=query(HEIDIAN, pms);
    destruct(pms);
    msg = HIC +LOCAL_MUD_NAME()+ HIY HEIDIAN_NAME HIC " 历代店主：\n"NOR;
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    if (!sizeof(heidian_record))
        msg += HIY "目前还没有数据。\n";
    else
    {
        msg += sprintf(HIW"%-25s%-30s%-10s%s\n"NOR,"姓名","拍卖时间","拍卖师","价格");
        for (i = 0;i < sizeof(heidian_record);i++)
            msg += sprintf(HIY"%-25s%-30s%-10s%d\n"NOR,
                   heidian_record[i]["name"]+"("+heidian_record[i]["id"]+")",
                   ctime(heidian_record[i]["time"]),
                   heidian_record[i]["pms"],
                   heidian_record[i]["value"]
                   );
    }
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    write(msg);
    return 1;
}