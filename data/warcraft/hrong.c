// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m踏雪[1;34m乌锥[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身如黑缎一般，四蹄白色，追风逐电、神骏非凡。[2;37;0m
它是花荣的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hrong");
        set("owner_name", "花荣");
        set_temp("owner", "hrong");
        set_temp("owner_name", "花荣");
        ::setup();
}
