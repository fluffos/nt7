// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m[5m赤炎[2;37;0m[2;37;0m", ({"ync"}));        
        set("gender", "男性");                
        set("long", "天外飞来一团炽热的火球，席卷着整个神州大地[2;37;0m
它是烟鬼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zzyyy");
        set("owner_name", "烟鬼");
        set_temp("owner", "zzyyy");
        set_temp("owner_name", "烟鬼");
        ::setup();
}
