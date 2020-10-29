//Cracked by Kafei
// 
inherit ITEM;

void create()
{
        set_name("黄药师手谕", ({"shou yu", "yu", "letter"}));
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "封");
                set("long","\n
=================================
|                                |
|                字                |
|                谕                |
|                灵                |
|                风                |
|                吾                |
|                徒                |
|                                |
|                        桃        |
|                        花        |
|                        黄        |
|                                |
|                        缄        |
|                                |
=================================\n");
                set("material", "paper");
        }
}