// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红[2;37;0m[2;37;0m", ({"xiaobb"}));        
        set("gender", "女性");                
        set("long", "小红[2;37;0m
它是雨雪纷纷的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lixbbb");
        set("owner_name", "雨雪纷纷");
        set_temp("owner", "lixbbb");
        set_temp("owner_name", "雨雪纷纷");
        ::setup();
}
