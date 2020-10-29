// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("油加栗[2;37;0m[2;37;0m", ({"youjia"}));        
        set("gender", "女性");                
        set("long", "绿油油的树[2;37;0m
它是无尾熊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wuweixiong");
        set("owner_name", "无尾熊");
        set_temp("owner", "wuweixiong");
        set_temp("owner_name", "无尾熊");
        ::setup();
}
