//redl 2014
#include <ansi.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "九老洞");
        set("long", @LONG
这是九老洞里的秘密隧道，深窈无比，神秘难测。你一走进来，
便发觉洞中叉叉洞多如迷宫，怪异莫测，似乎黝黑无底。洞里隐隐传
来鸡犬鼓乐之声，令人惊异间，忽有蝙蝠群涌而至扑熄火炬。还是快
快离开吧。
LONG );
        /*set("objects", ([
             __DIR__"npc/bianfu1" : 10,
        ]));*/
        set("exits", ([
                "north" : __DIR__"bfde4",
                "south" : __DIR__"bfde2",
/*                "south" : __DIR__"bfdd" + (string)random(20),
                "west" : __DIR__"bfdd" + (string)random(20),
                "east" : __DIR__"bfdd" + (string)random(20),
                "up" : __DIR__"bfdd" + (string)random(20),
                "down" : __DIR__"bfdd" + (string)random(20),*/
        ]));

        set("no_protect", 1); 
        set("n_time", 900 + random(30));  
        set("n_npc", 9);  
        set("n_max_npc", 9); 
        set("s_npc", "/d/emei/xue/npc/boss3");

                set("stop_run", random(2));
                set("du_time", time());
        setup();
}

void heart_beat()
{
        object enemy;
        object *enemies, *obs;
        mapping my;
        int itmp;
                
                if (query("du_time") < time()) {
                        
                        set("du_time", time() + 5);
                
                                obs = filter_array(all_inventory(this_object()),
                           (: $1->is_character() &&
                           query("id", $1) == "xixue bianfu"
                           :));
                           
                        if (sizeof(obs) > 0) {//有蝙蝠
                                
                                enemies = filter_array(all_inventory(this_object()),
                           (: playerp($1) //&&
                           :));
        
                        if (arrayp(enemies) && sizeof(enemies)) {foreach (enemy in enemies) {
                                my = enemy->query_entire_dbase();
                                
                                itmp = my["max_qi"] / 60; 
                                if (itmp < 1000000) itmp = 1000000;
                                my["eff_qi"] -= itmp; 
                                if (my["qi"] > my["eff_qi"]) my["qi"] = my["eff_qi"];
                                
                                itmp = my["max_jing"] / 60; 
                                if (itmp < 500000) itmp = 500000;
                                my["eff_jing"] -= itmp; 
                                if (my["jing"] > my["eff_jing"]) my["jing"] = my["eff_jing"];
                                
                                tell_object(enemy, BGRN + HIR + "蝙蝠喷出一口浓烟，你中毒了。\n" + NOR);
                                if (my["jing"] < 1 || my["qi"] < 1) {
                                        my["qi"] = my["eff_qi"] = -1;
                                        my["jing"] = my["eff_jing"] = -1;
                                        set_temp("die_reason", NOR + "被九老洞的蝙蝠毒死了" + NOR, enemy);
                                }
                                }
                        }
                        }
                }
        
        return ::heart_beat();
}


