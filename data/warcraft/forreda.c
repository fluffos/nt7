// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("张扬[2;37;0m[2;37;0m", ({"zhangyangb"}));        
        set("gender", "男性");                
        set("long", "张扬[2;37;0m
它是小红颜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "forreda");
        set("owner_name", "小红颜");
        set_temp("owner", "forreda");
        set_temp("owner_name", "小红颜");
        ::setup();
}
