// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("吊睛白额大猫[2;37;0m[2;37;0m", ({"akb"}));        
        set("gender", "男性");                
        set("long", "通体雪白，无一根杂毛[2;37;0m
它是伯赏坤毓的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "scdyxie");
        set("owner_name", "伯赏坤毓");
        set_temp("owner", "scdyxie");
        set_temp("owner_name", "伯赏坤毓");
        ::setup();
}
