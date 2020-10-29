// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m小白[2;37;0m[2;37;0m", ({"xbai"}));        
        set("gender", "女性");                
        set("long", "小白[2;37;0m
它是瑶瑶的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yaoyao");
        set("owner_name", "瑶瑶");
        set_temp("owner", "yaoyao");
        set_temp("owner_name", "瑶瑶");
        ::setup();
}
