// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m初升[1;35m之[1;33m阳[2;37;0m[2;37;0m", ({"sun"}));        
        set("gender", "男性");                
        set("long", "初升之阳[2;37;0m
它是欧霸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sunshine");
        set("owner_name", "欧霸");
        set_temp("owner", "sunshine");
        set_temp("owner_name", "欧霸");
        ::setup();
}
