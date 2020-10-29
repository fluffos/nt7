inherit ITEM;

void create()
{
   set_name("《三字经》", ({ "san zi jing","jing","book" }));
   set_weight(600);
   set("unit", "本");
   set("long","这是为了提高文化修养的书.\n");
   set("value", 300);
   set("skill", ([
     "name":      "literate",    
     "exp_required":   0, 
                         
     "sen_cost":     10,   
     "difficulty":   1, 
     "max_skill":   20,          
   ]) );
}