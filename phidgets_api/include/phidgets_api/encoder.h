#ifndef PHIDGETS_API_ENCODER_H
#define PHIDGETS_API_ENCODER_H

#include <functional>

#include <libphidget22/phidget22.h>

#include "phidgets_api/phidget22.h"

namespace phidgets {

class Encoder final
{
  public:
    PHIDGET22_NO_COPY_NO_MOVE_NO_ASSIGN(Encoder)

    explicit Encoder(
        int32_t serial_number, int hub_port, bool is_hub_port_device,
        int channel,
        std::function<void(int, int, double, int)> position_change_handler);

    ~Encoder();

    /** @brief Reads the current position of an encoder
     */
    int64_t getPosition() const;

    /** @brief Sets the offset of an encoder such that current position is the
     * specified value
     * @param position The new value that should be returned by
     * 'getPosition(index)' at the current position of the encoder*/
    void setPosition(int64_t position) const;

    /** @brief Gets the position of an encoder the last time an index pulse
     * occured. An index pulse in this context refers to an input from the
     * encoder the pulses high once every revolution.
     */
    int64_t getIndexPosition() const;

    /** @brief Checks if an encoder is powered on and receiving events
     */
    bool getEnabled() const;

    /** @brief Set the powered state of an encoder. If an encoder is not
     * enabled, it will not be given power, and events and changes in position
     * will not be captured.
     * @param enabled The new powered state of the encoder*/
    void setEnabled(bool enabled) const;

    void positionChangeHandler(int position_change, double time,
                               int index_triggered);

  private:
    int channel_;
    std::function<void(int, int, double, int)> position_change_handler_;
    PhidgetEncoderHandle encoder_handle_;

    static void PositionChangeHandler(PhidgetEncoderHandle phid, void *ctx,
                                      int position_change, double time_change,
                                      int index_triggered);
};

}  // namespace phidgets

#endif  // PHIDGETS_API_ENCODER_H
