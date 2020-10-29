//written by jinx@NT

inherit F_CLEAN_UP;

int main(object me,string arg)
{
     object *usr;
                       if (! SECURITY_D->valid_grant(me, "(admin)"))   
                                return 0; 
     usr=all_inventory(environment(me));

     foreach(object u in usr) {
     if( !userp(u)) continue;
      if( u==me ) continue;
     u->command("drop all");
     }
     write("Ok...\n");
     return 1;
}
