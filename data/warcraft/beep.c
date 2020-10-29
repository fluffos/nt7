// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青鸾[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "青鸾[2;37;0m
它是无花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "beep");
        set("owner_name", "无花");
        set_temp("owner", "beep");
        set_temp("owner_name", "无花");
        ::setup();
}
