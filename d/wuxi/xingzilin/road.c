// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <room.h>
#include <ansi.h>
inherit ROOM;

int clean_up() { return 1;}

string look_pai(object me);

void create()
{
        set("short", "杏林小道");
        set("long", 
"这是一条黄土小路，两旁的杏树薄雾飘绕。遥望东面又是一片茂密\n"
"的杏树林，隐约有人马的声音传来。路边的树上挂着一个"+CYN+"牌子"+NOR+"。\n"
);
        set("no_sleep_room",1);
        set("no_magic", 1);
        set("no_clean_up", 1);
        set("channel_id","挂级精灵");
        set("msg_hero", "无");
        set("exits", ([
                        "east"  : __DIR__"road2", 
                        "west" : "/d/wuxi/xinlin1",
        ]));
           set("objects", ([ 
                     "/clone/npc/walker"  : 1, 
           ])); 
        set("item_desc", ([
                "牌子": (: look_pai :),
                "pai": (: look_pai :),
                "paizi": (: look_pai :),
        ]) );
        
        setup();
        call_out("put_eren", 1800);
}

void init()
{
        if (playerp(this_player()))
        {
                if (!query("dynaroom_ok"))
                {
                        set("dynaroom_ok", 1, this_object());
                        load_object(__DIR__"dynaxzl.c")->create();
                }
                delete_temp("xzz", this_player());//连悲酥清风一起清除
        }
}

int valid_leave(object me, string dir)
{
        if (dir == "east" && ! playerp(me)) return 0; //阻挡npc进入区域
        if (dir == "east") {
                set_temp("xzz/ntrip", 0, me);//移动惩罚和杀怪数清0
                set_temp("xzz/nkill", 0, me);
                set_temp("xzz/ntrip2", 0, me);
                set_temp("xzz/nkill2", 0, me);
                set_temp("xzz/kar", 15 + random(19), me); 
                set_temp("xzz/entertime", time(), me); 
        }
        return ::valid_leave(me, dir);
}


mixed  put_eren()//放置恶人
{
                string str;
        object ob, eren, where, *ulist;
        int count;
        count = 0;
        ulist  =  users();
        str = "";
//              str = HIY + "玩家位置:\n";
        foreach (ob in ulist)
        {
                where = environment(ob);
                if (!where) continue;
//              if (where) str += NOR+"  "+ query("name", ob) + " = "+HIC+ query("short", where) + ((query("ngroup", where)==2) ? HIY+ " <-目标！" : "") + "\n" + NOR;
                        if (query("ngroup", where) && !query_temp("xzz/kar", ob)) set_temp("xzz/kar", 15 + random(19), ob); //防止意外出现在林子里的玩家出现异常
                        if (query("ngroup", where)==2)
                        {
                                if (random(100) <= (query_temp("xzz/kar", ob))) {
                                        message_vision(YEL "树林中突然传来几声阴笑，一个黑影纵身往$N扑去。\n" NOR, ob);
                                        eren = new(__DIR__"npc/eren");
                                        eren->move(where); 
                                        eren->set_leader(ob);
                                        count += 1;
                                        //如果刷怪数保持大于1000再次获得恶人的机会！这也可能是危险，所以要求站着的人手动走走去找boss
                                        if ((query_temp("xzz/nkill2", ob))>=1000 && random(100) <= (query_temp("xzz/kar", ob)))
                                        {
                                                message_vision(YEL "树林中突然又传来几声阴笑，一个黑影纵身往$N扑去。\n" NOR, ob);
                                                eren = new(__DIR__"npc/eren");
                                                eren->move(where); 
                                                eren->set_leader(ob);
                                                count += 1;
                                        }
                                }
                        }
                        if (sscanf(base_name(where), "/d/wuxi/xingzilin/%*s") && query_temp("xzz/entertime", ob)) str += "  " + HIC + query("family/family_name", ob) + query("family/title", ob) + " " + RED + query("name", ob) + NOR + "(" + query("id", ob) +")  - " + ctime( query_temp("xzz/entertime", ob) ) + "\n";
        }
//              write  (str);
                if (str == "") str = "无";
                set("msg_hero", str);
        CHANNEL_D->do_channel(this_object(),"sys", "杏子林挂级点深处投放了"+ count +"个四大恶人。\n");
                call_out("put_eren", 1200 + random(900));//随机是为了避免有机器人准时进去投机
        return 1;
}



string look_pai(object me)
{
        return 
HIY + "rideto wuxi,e,e,e,n,e,l pai\n" + NOR + 
HIG + "《杏子林》示意：\n" + HIC +
"※※※※※※※※※※※※※※\n" + 
"※              □□□□□※\n" + 
"※              □□□□□※\n" + 
"※      (深处)  □□□□□※\n" + 
"※              □□□□□※\n" + 
"※              □□□□□※\n" + 
"※                  ↑    ※\n" + 
"※                □□□  ※\n" + 
"           (外围) □□□  ※\n" + 
"                  □□□  ※\n" + 
"【无锡城东】        ↑    ※\n" + 
"杏林→□□□□□□□□    ※\n" + 
"                          ※\n" + 
"※※※※※※※※※※※※※※\n" + 
"\n" + NOR + 
HIG + " - 官府公告：\n" + NOR + 
"1)杏林到杏子林外围的小路上，小心西夏武士的埋伏，20lv以下的玩家切勿犯险\n" + 
"2)杏子林外围为固定大小，刷新六七八品武士\n" + 
"3)杏子林深处为不定大小，刷新二三四五品武士和一品高手四大恶人\n" + 
"4)外围和深处之间的岔道上，有一安全房间，其中有个丐帮长老可做任务\n" +
"5)杏子林遍布着悲酥清风和陷阱，"+HIR+"切忌横冲直闯"+NOR+"，用“maphere”查看地图\n" + 
"6)努尔海在杏子林外围，隐秘潜伏着极难出现，最好先大量击杀他手下的武士再行寻找\n" + 
"7)赫连铁树在杏子林深处出没，其余同上\n" + 
((query("msg_hero")=="无") ? "" : "\n\n" + HIG + "      《中原英雄立志榜》"+NOR+RED+"手印：\n" + query("msg_hero") + "\n" + NOR)
;
}

