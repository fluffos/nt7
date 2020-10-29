// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m白鸢[2;37;0m[2;37;0m", ({"baiyuan"}));        
        set("gender", "女性");                
        set("long", "美丽[2;37;0m
它是韩小戳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hanchat");
        set("owner_name", "韩小戳");
        set_temp("owner", "hanchat");
        set_temp("owner_name", "韩小戳");
        ::setup();
}
