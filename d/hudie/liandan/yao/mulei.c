#include <ansi.h>
//木类药材

inherit ITEM; 
mapping *ansi= ({
([     "yanse":    HIC,]),
([     "yanse":    HIG,]),
([     "yanse":    HIR,]),
([     "yanse":    HIB,]),
([     "yanse":    HIM,]),
([     "yanse":    HIY,]),
([     "yanse":    RED,]),
([     "yanse":    YEL,]), 
([     "yanse":    MAG,]),
([     "yanse":    CYN,]),

});
mapping *yao= ({
([     "name":     "杜仲",
       "id":       "du zhong",
       "yaoxing":  1000,
]),
([     "name":     "乌桕",
       "id":       "wu jiu",
       "yaoxing":  2000,
]),
([     "name":     "樟木",
       "id":       "zhang mu",
       "yaoxing":  3000,
]),
([     "name":     "厚朴",
       "id":       "hou pu",
       "yaoxing":  4000,
]),
([     "name":     "苏木",
       "id":       "su mu",
       "yaoxing":  5000,
]),
([     "name":     "沉香",
       "id":       "chen xiang",
       "yaoxing":  6000,
]),
([     "name":     "苦木",
       "id":       "ku mu",
       "yaoxing":  7000,
]),
([     "name":     "檀香",
       "id":       "tan xiang",
       "yaoxing":  8000,
]),
([     "name":     "黄柏",
       "id":       "huang bai",
       "yaoxing":  9000,
]),
});
void create()
{
    string name,id;
    int yaoxing,yaoo,yanse;

    yanse = random(sizeof(ansi));

    yaoo = random(sizeof(yao)); 

    name = yao[yaoo]["name"];

    id = yao[yaoo]["id"]; 

    yaoxing = yao[yaoo]["yaoxing"]; 

     //set_name(ansi[yanse]["yanse"]+name+NOR,({id}) );  
     set_name(name,({id}) );  

    set_weight(100);
    /*if( clonep() )
    set_default_object(__FILE__);
    else*/ {
         set("unit", "株");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }
