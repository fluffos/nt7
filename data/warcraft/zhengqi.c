// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m正气[2;37;0m[2;37;0m[2;37;0m", ({"zqj"}));        
        set("gender", "女性");                
        set("long", "正气麒麟[2;37;0m
它是正气诀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhengqi");
        set("owner_name", "正气诀");
        set_temp("owner", "zhengqi");
        set_temp("owner_name", "正气诀");
        ::setup();
}
