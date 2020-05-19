#include <oslib/oslib.h>
#include <unistd.h>

PSP_MODULE_INFO("MusicPlayer", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

OSL_IMAGE *background, *box, *controls;
int dir_index, first_pos = 1, cur_pos = 1, cur_pos_transparency = 10, transparency_index = 1, controls_transparency = 0, show_controls = 0;
char cur_dir[100] = "ms0:/MUSIC";
struct dirc
      {
            char name[45];
            int attr;
      } dir_content[256];


void load_screen(float load_state, float total)
{
    oslStartDrawing();
    
    oslDrawGradientRect(0, 0, 480, 272, RGB(0, 0, 0), RGB(50, 50, 50), RGB(100, 100, 100), RGB(150, 150, 150));
    oslDrawFillRect(50, 202, 430, 222, RGBA(255, 255, 255, 100));
    oslDrawFillRect(50, 202, 50+(430-50)*(load_state/total), 222, RGB(255, 0, 0));
    oslSetBkColor(RGBA(0, 0, 0, 0));
    oslDrawString((480-oslGetStringWidth("Loading..."))/2, 242, "Loading...");
    
    oslEndDrawing();
    oslSwapBuffers();
    oslEndDrawing();
}

void load_resources()
{
    load_screen(0, 3);
    
    controls = oslLoadImageFile("resource/controls.png", OSL_IN_RAM, OSL_PF_5551);
    load_screen(1, 3);
    
    background = oslLoadImageFile("theme/default/background.png", OSL_IN_RAM, OSL_PF_5551);
    load_screen(2, 3);
    
    box = oslLoadImageFile("theme/default/box.png", OSL_IN_RAM, OSL_PF_5551);
    box->centerX = box->sizeX / 2;
    box->centerY = box->sizeY / 2;
    load_screen(3, 3);
    
    if(!background || !box || !controls)
            oslDebug("Error while loading resources!");
    
    //while(1)
    sceKernelDelayThread(1000000);
}

void draw_on_screen()
{
     oslStartDrawing();
     
     int i = 1;
     oslDrawImageXY(background, 0, 0);
     oslSetAlpha(OSL_FX_ALPHA, 200);
     oslDrawImageXY(box, 240, 152);
     oslSetAlpha(OSL_FX_RGBA, 200);
     oslSetBkColor(RGBA(0, 0, 0, 0));
     oslSetTextColor(RGB(0,0,0));
     oslDrawString(70, 62, cur_dir);
     for(i=first_pos;i<=first_pos+13;i++)
                     {
                             if(i > dir_index)
                                  break;
                                  
                             if(dir_content[i].attr)
                                          oslSetTextColor(RGB(255,0,0));
                             else oslSetTextColor(RGB(0,0,255));
                             if(i-first_pos+1 == cur_pos)
                                  {
                                       oslSetBkColor(RGBA(0, 0, 0, cur_pos_transparency));
                                       if(cur_pos_transparency == 50)
                                               transparency_index = -1;
                                       else if(cur_pos_transparency == 10)
                                               transparency_index = 1;
                                       cur_pos_transparency += transparency_index;
                                  }
                             else oslSetBkColor(RGBA(0, 0, 0, 0));
                             
                             oslDrawString(80, 72+10*(i-first_pos+1), dir_content[i].name);
                     }
     if(dir_index > 14)
                  {
                       oslDrawFillRect(420, 82, 425, 222, RGBA(0, 0, 0, 50));
                       float bar_height = (222-82)*(14/(float)dir_index);
                       oslDrawFillRect(420, 82+(((float)first_pos-1)/(float)dir_index)*(222-82), 425, 82+(((float)first_pos-1)/(float)dir_index)*(222-82)+bar_height, RGBA(0, 0, 0, 255));
                  }

     if(show_controls || controls_transparency)
        {
            oslSetAlpha(OSL_FX_ALPHA, controls_transparency);
            oslDrawImageXY(controls, 0, 0);
            oslSetAlpha(OSL_FX_RGBA, controls_transparency);
            if(controls_transparency < 255 && show_controls)
               controls_transparency+=5;
            else if(controls_transparency > 0 && !show_controls)
                    controls_transparency-=5;
        }
     
     oslEndDrawing();
     oslSyncFrame();
}

void read_dir()
{
     int status, dfd;
     SceIoDirent dir;
     dir_index = 0;
     cur_pos = 1;
     first_pos = 1;

     dfd = sceIoDopen(cur_dir);

     if(dfd < 0)
            oslDebug("Error while opening folder!");
     
     status = sceIoDread(dfd, &dir);
     status = sceIoDread(dfd, &dir);
     do
       {
         status = sceIoDread(dfd, &dir);
         if(status > 0 && dir.d_stat.st_attr & FIO_SO_IFDIR)
                   {
                       dir_index++;
                       strcpy(dir_content[dir_index].name, dir.d_name);
                       if(strlen(dir_content[dir_index].name) >= 41)
                                 {
                                        int i;
                                        for(i=41;i<=43;i++)
                                               dir_content[dir_index].name[i] = '.';
                                        dir_content[dir_index].name[44] = '\0';
                                 }
                       dir_content[dir_index].attr = 1;
                   }
       }
     while(status > 0);
     if(status < 0)
               oslDebug("Error while reading folder (FIO_SO_IFDIR)!");
     sceIoDclose(dfd);
     
     dfd = sceIoDopen(cur_dir);
     do
       {
         status = sceIoDread(dfd, &dir);
         if(status > 0 && dir.d_stat.st_attr & FIO_SO_IFREG)
                   {
                       dir_index++;
                       strcpy(dir_content[dir_index].name, dir.d_name);
                       if(strlen(dir_content[dir_index].name) >= 41)
                                 {
                                        int i;
                                        for(i=41;i<=43;i++)
                                               dir_content[dir_index].name[i] = '.';
                                        dir_content[dir_index].name[44] = '\0';
                                 }
                       dir_content[dir_index].attr = 0;
                   }
       }
     while(status > 0);
     if(status < 0)
               oslDebug("Error while reading folder (FIO_SO_IFREG)!");
     sceIoDclose(dfd);
}

void read_keys()
{
     oslReadKeys();
     
     if (osl_keys->pressed.down)
        {
             if(cur_pos < 14 && cur_pos < dir_index)
                        cur_pos++;
             else if(first_pos+13 < dir_index)
                             first_pos++;
                  else {
                             cur_pos = 1;
                             first_pos = 1;
                       }
             return;
        }
     if (osl_keys->pressed.up)
        {
             if(cur_pos > 1)
                     cur_pos--;
             else if(first_pos > 1)
                          first_pos--;
                  else if(dir_index > 14)
                          {
                              cur_pos = 14;
                              first_pos = dir_index - 13;
                          }
                       else cur_pos = dir_index;
             return;
        }
     if(osl_keys->pressed.left)
           {
                  if(first_pos-13 < 1)
                           first_pos = 1;
                  else first_pos -= 13;
                  return;
           }
     if(osl_keys->pressed.right)
           {
                  if(first_pos+26 > dir_index && dir_index > 14)
                                  first_pos = dir_index - 13;
                  else if(dir_index > 14)
                                    first_pos += 13;
                  return;
           }
     if(osl_keys->pressed.circle)
        if(cur_dir[strlen(cur_dir)-1] != ':')
           {
                   cur_dir[strrchr(cur_dir, '/')-cur_dir] = '\0';
                   read_dir();
                   return;
           }
     if(osl_keys->pressed.cross)
           if(dir_content[first_pos+cur_pos-1].attr && dir_index)
                 {
                        strcat(cur_dir, "/");
                        strcat(cur_dir, dir_content[first_pos+cur_pos-1].name);
                        read_dir();
                        return;
                 }
     if(osl_keys->held.select)
           show_controls = 1;
     else show_controls = 0;
}

int main()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
    oslShowSplashScreen(1);
    
    load_resources();
    read_dir();
    
    oslSetKeyAutorepeat(OSL_KEYMASK_UP|OSL_KEYMASK_RIGHT|OSL_KEYMASK_DOWN|OSL_KEYMASK_LEFT|OSL_KEYMASK_R|OSL_KEYMASK_L, 40, 10);
    
    while(!osl_quit)
                    {
                            read_keys();
                            draw_on_screen();
                    }
                    
	oslEndGfx();
	oslQuit();
	return 0;
}
