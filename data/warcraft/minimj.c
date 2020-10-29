// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小青[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "女性");                
        set("long", "四大神兽[2;37;0m
它是一刀流的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "minimj");
        set("owner_name", "一刀流");
        set_temp("owner", "minimj");
        set_temp("owner_name", "一刀流");
        ::setup();
}
