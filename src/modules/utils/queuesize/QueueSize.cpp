/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

/*
QueueSize is an optional module that will always print the number of items in the Conveyer isr ring buffer
This could be used to always e.g. feed only as many GCODES to only e.g. fill the buffer to 5 items
*/

#include "QueueSize.h"
#include "libs/Module.h"
#include "libs/Kernel.h"

#include "utils.h"
#include "Gcode.h"
#include "StreamOutputPool.h"
#include "Conveyor.h"

QueueSize::QueueSize()
{
}

// Load module
void QueueSize::on_module_loaded()
{
    this->register_for_event(ON_GCODE_RECEIVED);
}

void QueueSize::on_gcode_received(void *argument)
{
    Gcode *gcode = static_cast<Gcode *>(argument);
    if(gcode->has_m && gcode->m == 542) {
	// get queue head and tail pointer
	unsigned int count = THECONVEYOR->get_queue_item_count_isr();
        gcode->stream->printf("queue_size: %d\n", count);
    }
}
