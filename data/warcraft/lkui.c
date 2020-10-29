// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m踏雪[1;34m乌锥[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身乌黑亮丽、宛如锦缎，唯有四蹄白色，龙吟虎步。[2;37;0m
它是李逵的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lkui");
        set("owner_name", "李逵");
        set_temp("owner", "lkui");
        set_temp("owner_name", "李逵");
        ::setup();
}
