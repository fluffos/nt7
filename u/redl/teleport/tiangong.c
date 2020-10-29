// This program is a part of NITAN MudLIB 
// redl 2013/9
//神器展览室的作用，玩家无法拾取
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

#define CREATE_INTERVAL 120             

int set_lv(object obj, int flag)
{
                if (!flag)
                {
                set("combat/MKS", 2100, obj);
                set("owner/redl", 21000000, obj);
                set("magic/imbue_ok", 1, obj);
                set("magic/blood", 21000, obj);
                set("ultimate/37", 1, obj);
                set("ultimate/39", 1, obj);
                set("enchase/flute", 9, obj);
                set("enchase/SN", 105, obj);
                IDENTIFY_D->identify_ultimate_ob(obj, 1);
                } else
                {
                set("combat/MKS", 2100, obj);
                set("owner/redl", 21000000, obj);
                set("magic/imbue_ok", 1, obj);
                set("magic/blood", 21000, obj);
                set("ultimate/37", 1, obj);
                set("ultimate/39", 1, obj);
                set("enchase/flute", 9, obj);
                set("enchase/SN", 121, obj);
                IDENTIFY_D->identify_ultimate_ob(obj, 1);
            }
        return 1;
}

int do_clear()
{
        object *inv;
        
                        inv = all_inventory();
                        if( sizeof(inv) > 0 ) {
                foreach( object ob2 in inv ) {
                        if( !ob2->is_character() ) {
                                        message_vision(append_color(NOR + CYN + "几个机关人冲过来，把$N" + NOR + CYN + "快速" + (random(2) ? "装进" : "扫到") + "垃圾袋里。\n" + NOR, CYN), ob2);
                                        destruct(ob2); 
                        }
                }
                }
                
        return 1;
}

int create_item()
{
        int rnd, i = random(5) + 4;
        object ob;
        string msg = "";
        
        remove_call_out("create_item");
        remove_call_out("do_clear");
        while (i--) {
                ob = EQUIPMENT_D->create_dynamic("", 60, 600);
        //      rnd = random(100);
//              //if (sscanf(base_name(ob), "/clone/tessera/%*s")) rnd = 100;//排除宝石
//              if (rnd<1) {
//                      CHANNEL_D->channel_broadcast("wiz", "太古" + base_name(ob) + "\n");
//                      set_lv(ob, 1);
//                      msg = HIK "黑白两色照耀天地，太古洪荒" + (random(2) ? "气息" : "味道") + "让人窒息...\n";
//              }
//              else if (rnd<10) {
//                      CHANNEL_D->channel_broadcast("wiz", "远古" + base_name(ob) + "\n");
//                      set_lv(ob, 0);
//                      msg = HIY "数颗流星疾射而过，远古蛮荒" + (random(2) ? "气息" : "味道") + "四散飘逸...\n";
//              }
                ob->move(this_object());
                message_vision(msg + HIC + (random(2) ? "哐啷" : "噹地") + "~" + (random(2) ? "~" : "") + "~一声，" + 
                                                                                     ob->name() + NOR + HIC + (random(2) ? "从天而降" : "掉下来") + 
                                                                                     "，" + (random(2) ? "差点" : "险些") + 
                                                                                      (random(2) ? "砸到你头上" : "落到云海下") + 
                                                                                      "，楼里" + (random(2) ? "传来" : "响起") + 
                                                                                      (random(2) ? "几句" : "两人的") + 
                                                                                      (random(2) ? "叫骂" : "吵架声") + "。\n" + NOR, 
                                                                             ob);
        }
        rnd = CREATE_INTERVAL / 2 + random(CREATE_INTERVAL / 2);
        call_out("do_clear", rnd * 9 / 10);
        call_out("create_item", rnd);
        return 1;
}

void create()
{
        set("short", "天宫宝楼");
        set("long", 
"这是云端之上的一坪绝地，常年不见风雨雷电，只有日月静静地\n"
"轮番流转。中央是座七层的木质楼阁，据说那上面是为天神打造神器\n"
"的处所，楼里隐约有打铁和画符的声音可闻。\n"
);
                set("exits",([ /* sizeof() == 1 */
                        "out" : __DIR__"teleport",
                ]));

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_magic", 1); 
        set("no_sleep_room", 1); 
        //set("no_get", 1);
        set("max_carry_user" ,16);
        set("max_carry_exit" ,"out");
        
        setup();
        call_out("create_item", 3);
}

int do_action(string arg)
{
        string action = query_verb();
        object ob, me = this_player();
        
        if (action=="get") {
                if (!arg || arg=="" || arg=="all") {
                                tell_object(me, NOR "你到底想拿什么？\n" NOR);
                                return -1;
                        }
                        
                        ob = present(arg, this_object());
                        if (!ob || !objectp(ob)) {
                                        tell_object(me, NOR "附近没有这样东西。\n" NOR);
                                        return -1;
                        }
                        if (!sscanf(base_name(ob), "/inherit/template/armor/%*s") && !sscanf(base_name(ob), "/inherit/template/weapon/%*s")) {
                                        tell_object(me, NOR "这样东西拿不起来。\n" NOR);
                                        return -1;
                        }
                        
                        if (sscanf(base_name(ob), "/inherit/template/weapon/%*s") ||
                                sscanf(base_name(ob), "/inherit/template/armor/finger%*s") ||
                                sscanf(base_name(ob), "/inherit/template/armor/hands%*s")
                                ) {
                                if (query("teleport/tweapon", me) < 1) {
                                        tell_object(me, NOR "你还没有购买天宫宝楼武器兑换券，指令<ntstore buy tweapon>。\n" NOR);
                                        return -1;
                                }
                                if (ob->move(me)) {
                                        addn("teleport/tweapon", -1, me);
                                        addn("teleport/log/tweapon", 1, me);
                                        message_vision(NOR "$N手疾眼快，飞快把$n" NOR "抢在手里。\n" NOR, me, ob);
                                } else {
                                        tell_object(me, NOR "你身上超重了？\n" NOR);
                                }
                                return 1;
                        }
                        
                        if (sscanf(base_name(ob), "/inherit/template/armor/%*s")) {
                                if (query("teleport/tarmor", me) < 1) {
                                        tell_object(me, NOR "你还没有购买天宫宝楼防具兑换券，指令<ntstore buy tarmor>。\n" NOR);
                                        return -1;
                                }
                                if (ob->move(me)) {
                                        addn("teleport/tarmor", -1, me);
                                        addn("teleport/log/tarmor", 1, me);
                                        message_vision(NOR "$N手疾眼快，飞快把$n" NOR "抢在手里。\n" NOR, me, ob);
                                } else {
                                        tell_object(me, NOR "你身上超重了？\n" NOR);
                                }
                                return 1;
                        }
                }
                
        return 0;
}

void init()
{
        object me = this_player();
        
        if ( wiz_level(me) < 7 ) add_action("do_action", "");
        
        return ::init();
}


