// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m粉狐[2;37;0m[2;37;0m", ({"pinkfox"}));        
        set("gender", "女性");                
        set("long", "$HIM$粉狐[2;37;0m
它是红樱桃的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cherry");
        set("owner_name", "红樱桃");
        set_temp("owner", "cherry");
        set_temp("owner_name", "红樱桃");
        ::setup();
}
