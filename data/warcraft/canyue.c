// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m月月[2;37;0m[2;37;0m", ({"yueyue"}));        
        set("gender", "男性");                
        set("long", "江湖小月月[2;37;0m
它是晓风残月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "canyue");
        set("owner_name", "晓风残月");
        set_temp("owner", "canyue");
        set_temp("owner_name", "晓风残月");
        ::setup();
}
