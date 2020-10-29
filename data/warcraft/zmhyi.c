// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凰儿[2;37;0m[2;37;0m", ({"aiwr"}));        
        set("gender", "女性");                
        set("long", "萌萌哒[2;37;0m
它是孙喵喵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zmhyi");
        set("owner_name", "孙喵喵");
        set_temp("owner", "zmhyi");
        set_temp("owner_name", "孙喵喵");
        ::setup();
}
