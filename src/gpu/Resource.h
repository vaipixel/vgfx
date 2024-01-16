//
// Created by Anatta Feng on 2024/1/15.
//

#pragma once

/**
 * The base class for GPU resource. Overriders the onReleaseGPU() method to free all GPU resources.
 * No backend API calls should be made during destructuring since there may be no GPU context that
 * is current on the calling thread. Note: Resource is not thread safe, do not assess any properties
 * of a Resource unless its associated device is locked.
 */
class Resource {

};