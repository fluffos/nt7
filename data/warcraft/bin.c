// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m中华[1;33m小龙[2;37;0m[2;37;0m", ({"binbin"}));        
        set("gender", "男性");                
        set("long", "这是伴随小纯一起成长的青龙兽[2;37;0m
它是小纯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bin");
        set("owner_name", "小纯");
        set_temp("owner", "bin");
        set_temp("owner_name", "小纯");
        ::setup();
}
