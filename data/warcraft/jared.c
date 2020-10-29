// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小四[2;37;0m[2;37;0m", ({"xiaosi"}));        
        set("gender", "男性");                
        set("long", "看起来威武雄壮[2;37;0m
它是小半道的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jared");
        set("owner_name", "小半道");
        set_temp("owner", "jared");
        set_temp("owner_name", "小半道");
        ::setup();
}
