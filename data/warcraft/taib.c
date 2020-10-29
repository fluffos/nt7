// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m梅花鹿[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "$HIY$梅花鹿[2;37;0m
它是太白金星的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "taib");
        set("owner_name", "太白金星");
        set_temp("owner", "taib");
        set_temp("owner_name", "太白金星");
        ::setup();
}
