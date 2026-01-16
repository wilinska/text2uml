#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_HEAD_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_HEAD_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/arrow_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/circle_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/open_arrow_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/open_rhomb_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/rhomb_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/square_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/three_lines_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_ends_definitions/x_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/arrow_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/circle_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/open_arrow_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/open_rhomb_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/rhomb_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/square_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/three_lines_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_starts_definitions/x_injector.hpp"
#include "src/cpp/image_builder/injectors/i_injector.hpp"

class EdgeHeadInjector : public IInjector
{
public:
  explicit EdgeHeadInjector(XMLDocument &doc)
      : doc_(doc),
        end_arrow_(doc),
        end_open_arrow_(doc),
        end_rhomb_(doc),
        end_open_rhomb_(doc),
        end_square_(doc),
        end_x_(doc),
        end_three_lines_(doc),
        end_circle_(doc),
        start_arrow_(doc),
        start_open_arrow_(doc),
        start_rhomb_(doc),
        start_open_rhomb_(doc),
        start_square_(doc),
        start_x_(doc),
        start_three_lines_(doc),
        start_circle_(doc)
  {
  }

  void Inject(LineHeadEnum line_end, bool start)
  {
    if (start)
    {
      switch (line_end)
      {
      case LineHeadEnum::Arrow: start_arrow_.Inject(); break;
      case LineHeadEnum::OpenArrow: start_open_arrow_.Inject(); break;
      case LineHeadEnum::Rhomb: start_rhomb_.Inject(); break;
      case LineHeadEnum::OpenRhomb: start_open_rhomb_.Inject(); break;
      case LineHeadEnum::Square: start_square_.Inject(); break;
      case LineHeadEnum::Cross: start_x_.Inject(); break;
      case LineHeadEnum::ThreeLines: start_three_lines_.Inject(); break;
      case LineHeadEnum::Circle: start_circle_.Inject(); break;
      default: break;
      }
    }
    else
    {
      switch (line_end)
      {
      case LineHeadEnum::Arrow: end_arrow_.Inject(); break;
      case LineHeadEnum::OpenArrow: end_open_arrow_.Inject(); break;
      case LineHeadEnum::Rhomb: end_rhomb_.Inject(); break;
      case LineHeadEnum::OpenRhomb: end_open_rhomb_.Inject(); break;
      case LineHeadEnum::Square: end_square_.Inject(); break;
      case LineHeadEnum::Cross: end_x_.Inject(); break;
      case LineHeadEnum::ThreeLines: end_three_lines_.Inject(); break;
      case LineHeadEnum::Circle: end_circle_.Inject(); break;
      default: break;
      }
    }
  }

  XMLDocument &GetXMLDocument() { return doc_; }

private:
  XMLDocument &doc_;

  EdgeEndArrowInjector end_arrow_;
  EdgeEndOpenArrowInjector end_open_arrow_;
  EdgeEndRhombInjector end_rhomb_;
  EdgeEndOpenRhombInjector end_open_rhomb_;
  EdgeEndSquareInjector end_square_;
  EdgeEndXInjector end_x_;
  EdgeEndThreeLinesInjector end_three_lines_;
  EdgeEndCircleInjector end_circle_;

  EdgeStartArrowInjector start_arrow_;
  EdgeStartOpenArrowInjector start_open_arrow_;
  EdgeStartRhombInjector start_rhomb_;
  EdgeStartOpenRhombInjector start_open_rhomb_;
  EdgeStartSquareInjector start_square_;
  EdgeStartXInjector start_x_;
  EdgeStartThreeLinesInjector start_three_lines_;
  EdgeStartCircleInjector start_circle_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_HEAD_INJECTOR_HPP
