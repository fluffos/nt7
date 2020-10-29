// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蒂法[2;37;0m[2;37;0m", ({"faustion"}));        
        set("gender", "女性");                
        set("long", "不长毛的美少女蒂法[2;37;0m
它是爱是唯一的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "iswear");
        set("owner_name", "爱是唯一");
        set_temp("owner", "iswear");
        set_temp("owner_name", "爱是唯一");
        ::setup();
}
