// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m踏雪[5m[1;34m乌锥[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身乌黑宛如锦缎，唯有四蹄白色，追风逐电，龙吟虎相。[2;37;0m
它是杨三泰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ship");
        set("owner_name", "杨三泰");
        set_temp("owner", "ship");
        set_temp("owner_name", "杨三泰");
        ::setup();
}
