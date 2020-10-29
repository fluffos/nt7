// counter.h
//wsw于2004年2月20日
//玩家柜台
//玩家有此柜台后，可把物品摆在柜台上出售，重启后保留。
//如果是随机属性物品，物品->set("changed",1)

#include <ansi.h>   
inherit F_SAVE;   
inherit ITEM;

void init () ;
void setup();
string query_save_file();
int save();
int do_sell(string arg);
int do_buy(string arg) ;
int do_look(string arg);
int do_qu(string arg);
object get_item(object ob,int place);
  
void init ()   
{   
  add_action ("do_sell","sell");   
  add_action ("do_buy","buy"); 
  add_action ("do_look","look"); 
  add_action ("do_qu","qu"); 

}

void setup()
{
        ::setup();
        restore();
}   
string query_save_file()  
{  
   string id;  

   id=file_name(this_object());
   id = id[strsrch(id,"/",-1)+1..strsrch(id,"#",1)-1] ;
   if( !id ) return 0;  
   return sprintf("/data/playercity/obj/counter/%s", id);  
}  
  
int save()  
{  
   return ::save();  
}  

int do_sell(string arg)  
{  
        object obj,newobj;  
        object me= this_player();  
        object ob= this_object();  
        string thing,str;  
        int place,price,j;  

        if(!arg)  
                return notify_fail("你准备卖什么东西？<指令>:sell <物品ID> at <位置号> for <单价>\n");  

        if(ob->query("owner_id")!=me->query("id")) 
                return notify_fail("这不是你的柜台。\n");

        if(me->is_busy()) 
                return notify_fail("你正忙着呢！\n");  

        if (sscanf(arg,"%s at %d for %d",thing,place,price)!=3)     
                return notify_fail("你要把什么物品放在柜台的哪个位置？<指令>:sell <物品ID> at <位置号> for <单价>\n");    
              
        if (price<=0) return notify_fail("象你这样的好心人，现在不多了！\n");

        if (!( obj=present (thing,me)))   
                return notify_fail("你身上没有这个物品。\n");   

        if (obj->is_character()
             || obj->query_max_encumbrance()  
            || obj->query("liquid")  
                || obj->query_unique())  
                return notify_fail("这样东西可不能卖。\n");  
                
        if (obj->query("equipped")) 
                return notify_fail("你先脱下来吧。\n");  

        if (place <1 || place >ob->query("capacity"))  
                return notify_fail("这个柜台只能摆"+ob->query("capacity")+"件物品。\n");  

        if (ob->query("place_"+place+"/have")=="have")  
                return notify_fail("柜台第"+place+"个位置已经有物品了。\n");  

        ob->set("place_"+place+"/have","have");
        ob->set("place_"+place+"/file_name",base_name(obj));
        if (obj->query_amount()) ob->set("place_"+place+"/amount",obj->query_amount());
        else ob->set("place_"+place+"/amount",1);
        ob->set("place_"+place+"/price",price);
        ob->set("place_"+place+"/attribute",obj->query_entire_dbase());

        ob->save();  
        message_vision("$N把一"+obj->query("unit")+obj->name()+NOR+"摆进柜台。\n",me);
        obj->move(VOID_OB);  
        destruct(obj);  
        me->start_busy(2); 
        return 1;
}     
 
int do_buy(string arg)  
{ 
        object newobj;  
        object me= this_player();  
        object ob= this_object(); 
        mapping attribute;  
        int place,afford,price;  
        if(!arg)  
                return notify_fail("你要买什么？<指令>:buy <序号> from counter\n");  

        if(me->is_busy()) 
                return notify_fail("你正忙着呢！n");    

        if (sscanf(arg,"%d from counter",place)!=1)     
                return notify_fail("你要买什么位置的物品？<指令>:na xxx from bag\n"); 

        if (place <1 || place >ob->query("capacity"))  
                return notify_fail("柜台只有"+ob->query("capacity")+"个空间。\n");  

        if (ob->query("place_"+place+"/have")!="have")  
                return notify_fail("柜台第"+place+"个空间是空的。\n");  
         
       price=ob->query("place_"+place+"/price");
       if (me->query("stocks/balance") < price && ob->query("owner_id") != me->query("id")) 
                return notify_fail("你的YSG不够。\n");
       newobj=get_item(ob,place);
       if(newobj && newobj->move(me)) 
       {             
          if(ob->query("owner_id") != me->query("id")) {
                  me->add("stocks/balance",-1*price);
                  ob->add("payment",price);
          }
          ob->add("place_"+place+"/amount",-1);
          if (ob->query("place_"+place+"/amount")<=0)
              ob->delete("place_"+place);
                  if(ob->query("owner_id") != me->query("id"))
                  message_vision("$N买下了一"+newobj->query("unit")+newobj->name()+NOR+"。\n",me); 
          else message_vision("$N从柜台上撤下了一"+newobj->query("unit")+newobj->name()+NOR+"。\n",me); 
          ob->save();
          me->save();
          me->start_busy(2);
                 return 1;
        }else{
                destruct(newobj);
                return notify_fail("买物品失败。\n");
        }
}

int do_look(string arg)
{
    string str;
    object obj,ob;
    int place,j;
    
    ob=this_object();
    
    if (!arg) return 0;
    if (arg == "counter") {
            str=HIB"玩家之城的柜台。\n"NOR;
            str+="查看物品详细资料：look <序号> in counter 。\n";
            str+="摆上物品准备出售：sell <物品ID> at <序号> for <单价>\n";
            str+="卖下柜台里的物品：buy <序号> from counter\n";
            str+="取出柜台里的货款：qu <数量> from counter\n";
            str+="┌——————————————————————————————————————┐\n";
            str+=   "│序号   物品名称     ID                 数量        单价\n";  
            str+="├——————————————————————————————————————┤\n";
            for (j = 1; j<ob->query("capacity")+1; j++) { 
            if (ob->query("place_"+j+"/have")=="have")
                    str+=sprintf("│%2d：%16' 's\t%16' 's\t%d\t%d\t\t\t│\n",j,ob->query("place_"+j+"/attribute/name"),
                    ob->query("place_"+j+"/attribute/id"),ob->query("place_"+j+"/amount"),
                    ob->query("place_"+j+"/price"));
            else  str+=sprintf("│%2d： <空>\t\t\t\t\t\t\t\t│\n",j);
       }
        str+="└——————————————————————————————————————┘\n";  
        str+="当前货款："+ob->query("payment")+"。\n"; 
        write(str);
        return 1;
    }
    
    if (sscanf(arg,"%d in %s",place,str)==2) {
            if (str!="counter") return 0;
            if (ob->query("place_"+place+"/have")=="have") {
                    obj=get_item(ob,place);
                    if (objectp(obj)) {
                            if (obj->query("changed")) 
                                    "/cmds/std/ll.c"->look_item(0,obj);
                            else "cmds/std/look.c"->look_item(this_player(),obj);
                            destruct(obj);
                            return 1;
                    }
            }else write("这个位置是空的。\n");
            return 1;        
    } 
    return 0;
}

int do_qu(string arg)  
{  
        object obj,newobj;  
        object me= this_player();  
        object ob= this_object();  
        string thing,str;  
        int place,price,j; 
         
        if(ob->query("owner_id")!=me->query("id")) 
                return notify_fail("你想当小偷？？\n");        
        if(!arg)  
                return notify_fail("你要取多少钱？<指令>:qu <数量> from counter\n");  
        if(me->is_busy()) 
                return notify_fail("你正忙着呢！\n");  
        if (sscanf(arg,"%d from counter",price)!=1)     
                return notify_fail("你要取多少钱？<指令>:qu <数量> from counter\n");
                  
        if (price <= 0) return notify_fail("你想干嘛呢？\n");

        if (ob->query("payment") < price) return notify_fail("柜台里没有这么多货款。\n");

        ob->add("payment",-1 * price);
        me->add("stocks/balance", price);
        me->start_busy(2);
        message_vision("$N从柜台上取出"+ price +" YSG的货款并存入了股市。\n",me); 
        
        ob->save();
        me->save();
        return 1;
        
}

object get_item(object ob,int place)
{
    object obj;
    mapping attribute;
    string *key;
    int j;
    
    obj=new(ob->query("place_"+place+"/file_name"));  
    if(!obj)  return 0; 
    attribute=ob->query("place_"+place+"/attribute");
    if (mapp(attribute)) {
             key=keys(attribute);
               key = sort_array(key, 0);
            for(j=0; j<sizeof(key); j++) {
                obj->set(key[j], attribute[key[j]]); 
            }                
    }
    return obj;        
        
}