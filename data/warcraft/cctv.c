// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("舞海虎[2;37;0m[2;37;0m", ({"ccgg"}));        
        set("gender", "男性");                
        set("long", "没得[2;37;0m
它是小云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cctv");
        set("owner_name", "小云");
        set_temp("owner", "cctv");
        set_temp("owner_name", "小云");
        ::setup();
}
